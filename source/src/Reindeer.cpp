/*
 * author:  Alexander Grill
 * file:    Reindeer.cpp
 * project: santa_claus_problem
 * date:    01.01.2021
*/

#include "Reindeer.h"

#include "rang.hpp"

#include <thread>
#include <random>
#include <iostream>

using namespace std;
using namespace rang;

void Reindeer::comeback(){
    while (readytofly == false && christmas == false){
        unique_lock<std::mutex> ulr{mxr};
        random_device rd;
        mt19937 gen{rd()};
        uniform_real_distribution<> dis{0.5, 1.5};
        double time = dis(gen);
        int t = time * 1000;
        this_thread::sleep_for(std::chrono::milliseconds(t));
        reindeer += 1;
        cout << fg::blue << reindeer << " Reindeer are in the stable\n" << flush;
        if (reindeer == 9){
            sc.set_enoughtreindeer();
            sc.santaSem.notify_one();
        }
        if (reindeerSem.wait_for(ulr, 1s, [&] { return readytofly == true; })){
            getHitched();
        }
    }
}

int Reindeer::getReindeer(){
    return reindeer;
}

void Reindeer::resetReindeer(){
    reindeer = 0;
}

void Reindeer::getHitched(){
    cout << fg::yellow << "Reindeers are hichted by Santa\n" << flush;
    this_thread::sleep_for(3s);
    cout << fg::green << "Santa we can fly\n" << flush;
    cout << fg::green << "Merry Christmas Ho Ho Ho\n" << flush;
}
void Reindeer::setSanta(SantaClaus& s){
    sc = s;
}