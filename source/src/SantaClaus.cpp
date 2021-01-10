/*
 * author:  Alexander Grill
 * file:    SantaClaus.h
 * project: santa_claus_problem
 * date:    01.01.2021
*/

#include "SantaClaus.h"

#include "rang.hpp"

#include <mutex>
#include <iostream>

using namespace std;
using namespace rang;


void SantaClaus::sleep(){
    unique_lock<mutex> ulfg{mxs};
    while(true){
        santaSem.wait(ulfg, [&]() { return doaction == true; });
        cout << fg::magenta << "Santa wack up!\n" << flush;
        if (ren.getReindeer() == 9 && !readytofly){
            readytofly = true;
            ren.reindeerSem.notify_one();
            ren.resetReindeer();
            doaction = false;
            }
        if (elv.getElves() == 3 && !readytohelp){
            readytohelp = true;
            elv.elfTex.notify_one();
            doaction = false;
        }
        if(readytofly){
            return;
        }
    }
}

void SantaClaus::set_doaction(){
    doaction = true;
}

bool SantaClaus::get_readytofly(){
    return readytofly;
}