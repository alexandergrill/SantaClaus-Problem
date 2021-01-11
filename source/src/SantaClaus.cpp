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

using namespace std;
using namespace rang;


void SantaClaus::sleep(){
    unique_lock<mutex> ulfg{mxs};
    while (true){
        spdlog::get("console")->info("Encoding successfull Santa");
        if (readytofly || christmas)
        {
            return;
        }
        santaSem.wait(ulfg, [&]() { return doaction == true; });
        cout << fg::magenta << "Santa wack up!\n" << flush;
        if (ren.get_Reindeer() == ren.get_MaxReindeer() && !readytofly)
        {
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