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
    mutex m;
    unique_lock<mutex> ulfg{mxs};
    santaSem.wait(ulfg, [&]() { return enoughtelves == true || enoughtreindeer == true; });
    if (ren.getReindeer() == 9){
        ren.reindeerSem.notify_one();
        readytofly = true;
        ren.resetReindeer();
        }
    if (elv.getElves() == 3){
            elv.getHelp();
            cout << "servus santa" << endl;
        }
}

void SantaClaus::set_enoughtreindeer(){
    enoughtreindeer = true;
}
void SantaClaus::set_enoughtelves(){
    enoughtelves = true;
}

bool SantaClaus::get_readytofly(){
    return readytofly;
}