/*
 * author:  Alexander Grill
 * file:    SantaClaus.h
 * project: santa_claus_problem
 * date:    01.01.2021
*/

#include "SantaClaus.h"

#include <mutex>

using namespace std;


void SantaClaus::sleep(){
    while (readytofly == false && christmas == false){
        unique_lock<mutex> ul{mxs};
        santaSem.wait(ul, [&]() { return enoughtelves == true || enoughtreindeer == true; });
        if (ren.getReindeer() == 9){
            ren.reindeerSem.notify_one();
            readytofly = true;
            ren.resetReindeer();
        }
        if (elv.getElves() == 3){
            elv.getHelp();
        }
    }
}

void SantaClaus::set_enoughtreindeer(){
    enoughtreindeer = true;
}
void SantaClaus::set_enoughtelves(){
    enoughtelves = true;
}