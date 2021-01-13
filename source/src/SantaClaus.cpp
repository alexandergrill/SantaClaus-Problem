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

#include <rang/rang.hpp>

#include <mutex>
#include <iostream>

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
        if(christmas == true){
            return;
        }
        cout << fg::magenta << "Santa wack up!\n" << flush;
        if (ren.get_Reindeer() == ren.get_MaxReindeer() && !readytofly){
            readytofly = true;
            ren.reindeerSem.notify_one();
            //ren.reset_Reindeer();
            doaction = false;
        }
        if (elv.get_Elves() == elv.get_MaxElves() && !readytohelp && christmas == false){
            readytohelp = true;
            elv.elfTex.notify_one();
            doaction = false;
        }
    }
}

/*
-Name: double get_Blithelytime
-Beschreibung: gibt die Zeit aus, die Santa munter war
-Input: 
-Output: double get_Blithelytime  
*/
int SantaClaus::get_Blithelytime(){
    return blithelytime;
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
-Beschreibung: gibt true, false zurück je nachdem wie viele Elfen Santa benötigen
-Input: 
-Output: bool readytohelp   
*/
bool SantaClaus::get_Readytohelp(){
    return readytohelp;
}

/*
-Name: double set_Blithelytime
-Beschreibung: addiert die Zeit, in der Santa munter war
-Input: double t
-Output:
*/
void SantaClaus::set_Blithelytime(double t){
    blithelytime += t;
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