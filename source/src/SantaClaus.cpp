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
    santaSem.wait(ulfg, [&]() { return enoughtelves == true || enoughtreindeer == true; });
    if (ren.getReindeer() == 9){
        readytofly = true;
        ren.reindeerSem.notify_one();
        ren.resetReindeer();
        }
    if (elv.getElves() == 3){
        readytohelp = true;
        elv.elfTex.notify_one();
        cout << "rf" << get_readytofly() << endl;
        cout << "rh" << get_readytohelp() << endl;
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