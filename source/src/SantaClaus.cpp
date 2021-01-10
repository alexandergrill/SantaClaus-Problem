/*
 * author:  Alexander Grill
 * file:    SantaClaus.h
 * project: santa_claus_problem
 * date:    01.01.2021
*/

#include "SantaClaus.h"

#include <mutex>
#include <iostream>

using namespace std;


void SantaClaus::sleep(){
    unique_lock<mutex> ulfg{mxs};
    while(true){
        santaSem.wait(ulfg, [&]() { return doaction == true; });
        if (ren.getReindeer() == 9 && !readytofly){
            readytofly = true;
            ren.reindeerSem.notify_one();
            ren.resetReindeer();
            doaction = false;
            }
        if (elv.getElves() == 3 && !readytohelp){
            readytohelp = true;
            elv.elfTex.notify_one();
            cout << "rf" << get_readytofly() << endl;
            cout << "rh" << get_readytohelp() << endl;
            cout << "servus santa" << endl;
            doaction = false;
        }
        if(readytohelp && readytofly){
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