/*
 * author:  Alexander Grill
 * file:    SantaClaus.h
 * project: santa_claus_problem
 * date:    01.01.2021
*/

#include "SantaClaus.h"
#include "utils.h"

#include "rang.hpp"

#include <mutex>
#include <iostream>

using namespace std;
using namespace rang;

void SantaClaus::sleep(){
    unique_lock<mutex> ulfg{mxs};
    while(christmas == false){
        santaSem.wait(ulfg, [&]() { return doaction == true; });
        cout << fg::magenta << "Santa wack up!\n" << flush;
        if (ren.get_Reindeer() == ren.get_MaxReindeer() && !readytofly){
            readytofly = true;
            ren.reindeerSem.notify_one();
            ren.reset_Reindeer();
            doaction = false;
            }
        if (elv.get_Elves() == 3 && !readytohelp){
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

bool SantaClaus::get_readytohelp(){
    return readytohelp;
}

void SantaClaus::set_readytohelp(){
    readytohelp = false;
}