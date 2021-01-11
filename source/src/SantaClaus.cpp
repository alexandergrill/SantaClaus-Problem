/*
 * author:  Alexander Grill
 * file:    SantaClaus.h
 * project: santa_claus_problem
 * date:    01.01.2021
*/

#include "SantaClaus.h"
#include "utils.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

#include "rang.hpp"

#include <mutex>
#include <iostream>
#include <chrono>

using namespace std;
using namespace rang;


void SantaClaus::sleep(){
    unique_lock<mutex> ulfg{mxs};
    while (readytofly == false){
        santaSem.wait(ulfg, [&]() { return doaction == true; });
        auto t1 = chrono::high_resolution_clock::now();
        if(christmas == true){
            return;
        }
        cout << fg::magenta << "Santa wack up!\n" << flush;
        if (ren.get_Reindeer() == ren.get_MaxReindeer() && !readytofly){
            readytofly = true;
            ren.reindeerSem.notify_one();
            ren.reset_Reindeer();
            doaction = false;
        }
        if (elv.get_Elves() == 3 && !readytohelp && christmas == false)
        {
            readytohelp = true;
            elv.elfTex.notify_one();
            doaction = false;
        }
        auto t2 = chrono::high_resolution_clock::now();
        auto int_s = chrono::duration_cast<chrono::seconds>(t2 -t1);
        blithelytime += int_s.count();
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