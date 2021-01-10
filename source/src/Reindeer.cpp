/*
 * author:  Alexander Grill
 * file:    Reindeer.cpp
 * project: santa_claus_problem
 * date:    01.01.2021
*/

#include "Reindeer.h"
#include "utils.h"

#include "rang.hpp"

#include <thread>
#include <iostream>

using namespace std;
using namespace rang;

void Reindeer::comeback(){
    while (sc->get_readytofly() == false){
        unique_lock<std::mutex> ulr{mxr};
        int t = get_randomnum(0.5, 1.5) * 1000;
        this_thread::sleep_for(std::chrono::milliseconds(t));
        reindeer += 1;
        cout << fg::blue << reindeer << " Reindeer are in the stable\n" << flush;
        if (reindeer == 9){
            sc->set_doaction();
            sc->santaSem.notify_one();
        }
        if (reindeerSem.wait_for(ulr, 1s, [&] { return sc->get_readytofly() == true; })){
            get_Hitched();
        }
    }
}

int Reindeer::get_Reindeer(){
    return reindeer;
}

void Reindeer::reset_Reindeer(){
    reindeer = 0;
}

void Reindeer::get_Hitched(){
    cout << fg::yellow << "Reindeers are hichted by Santa\n" << flush;
    this_thread::sleep_for(3s);
    cout << fg::green << "Santa we can fly\n" << flush;
    cout << fg::green << "Merry Christmas Ho Ho Ho\n" << flush;
}
void Reindeer::set_Santa(SantaClaus* s){
    sc = s;
}