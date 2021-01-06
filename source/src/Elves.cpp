/*
 * author:  Alexander Grill
 * file:    Elves.cpp
 * project: santa_claus_problem
 * date:    01.01.2021
*/

#include "Elves.h"

#include "rang.hpp"

#include <thread>
#include <random>
#include <iostream>

using namespace std;
using namespace rang;

void Elves::tinker(){
    while (readytofly == false && christmas == false){
        unique_lock<mutex> ulh{mxe};
        random_device rd;
        mt19937 gen{rd()};
        uniform_real_distribution<> dis{0.5, 1.2};
        double time = dis(gen);
        int t = time * 1000;
        this_thread::sleep_for(chrono::milliseconds(t));
        elves += 1;
        cout << fg::cyan << elves << " Elves need help\n" << flush;
        if (elves == 3){
            sc.set_enoughtelves();
            cout << "hello elves" << endl;
            sc.santaSem.notify_one();
            this_thread::sleep_for(3s);
        }
    }
}

void Elves::getHelp(){
    while (elves < 0){
        unique_lock<mutex> ulg{mxe};
        random_device rd;
        mt19937 gen{rd()};
        uniform_real_distribution<> dis{0.1, 1.5};
        double time = dis(gen);
        int t = time * 1000;
        this_thread::sleep_for(chrono::milliseconds(t));
        cout << fg::blue << (elves - 3) * -1 << " elves helped\n"<< flush;
        elves -= 1;
    }
}

int Elves::getElves(){
    return elves;
}

void Elves::setSanta(SantaClaus& s){
    sc = s;
}