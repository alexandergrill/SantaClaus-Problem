/*
 * author:  Alexander Grill
 * file:    Elves.cpp
 * project: santa_claus_problem
 * date:    01.01.2021
*/

#include "Elves.h"
#include "utils.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

#include "rang.hpp"

#include <thread>
#include <random>
#include <iostream>

using namespace std;
using namespace rang;



void Elves::tinker(){
    unique_lock<mutex> ulh{mxe};
    while (sc->get_readytofly() == false && christmas == false){
        if (elves != 3){
            int t = get_randomnum(0.5, 1.0) * 1000;
            this_thread::sleep_for(chrono::milliseconds(t));
            elves += 1;
            elvessum += 1;
            cout << fg::cyan << elves << " Elves need help\n" << flush;
            spdlog::get("console")->info("A Elve is waiting for Santa´s Help");
        }
        if (elfTex.wait_for(ulh, 1s, [&] { return sc->get_readytohelp() == true; })){
            if(sc->get_readytofly() == false){
                get_Help();
                elves = 0;
                cout << fg::magenta << "Santa go sleep!\n" << flush;
            }
       }
       if (elves == 3 && christmas == false){
           sc->set_doaction();
           sc->santaSem.notify_one();
       }
    }
}

void Elves::get_Help(){
    while (elves > 0){
        random_device rd;
        mt19937 gen{rd()};
        uniform_real_distribution<> dis{0.1, 0.5};
        double time = dis(gen);
        int t = time * 1000;
        this_thread::sleep_for(chrono::milliseconds(t));
        cout << fg::cyan << (elves - 4) * -1 << " elves helped\n"<< flush;
        elves -= 1;
    }
    sc->set_readytohelp();
}

int Elves::get_SumElves(){
    return elvessum;
}

int Elves::get_Elves(){
    return elves;
}

void Elves::set_Santa(SantaClaus* s){
    sc = s;
}