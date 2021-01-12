/*
 * author:  Alexander Grill
 * file:    SantaClaus.h
 * project: santa_claus_problem
 * date:    01.01.2021
*/

//includes
#include "SantaClaus.h"
#include "utils.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

#include "rang.hpp"

#include <mutex>
#include <iostream>
#include <chrono>

//namespaces
using namespace std;
using namespace rang;

//Methoden Definitionen

/*
-Name: void sleep
-Beschreibung: Santa schläft und wird geweckt, wenn alle Rentiere zurück sind oder Elfen ihm brauchen
-Input: 
-Output:        
*/
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
        if (elv.get_Elves() == elv.get_MaxElves() && !readytohelp && christmas == false)
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

/*
-Name: bool get_Readytofly
-Beschreibung: gibt true, false zurück je nachdem wie viele Rentiere zurück gekommen sind
-Input: 
-Output: bool readytofly     
*/
bool SantaClaus::get_Readytofly(){
    return readytofly;
}

/*
-Name: bool get_Readytohelp
-Beschreibung: gibt true, false zurück je nachdem wie viele Elven Santa benötigen
-Input: 
-Output: bool readytohelp   
*/
bool SantaClaus::get_Readytohelp(){
    return readytohelp;
}

/*
-Name: void set_Readytohelp
-Beschreibung: setzt die Variable readytohelp auf false
-Input: 
-Output:        
*/
void SantaClaus::set_Readytohelp(){
    readytohelp = false;
}

/*
-Name: void set_Doaction
-Beschreibung: setzt die Variable doaction auf true
-Input: 
-Output:        
*/
void SantaClaus::set_Doaction(){
    doaction = true;
}