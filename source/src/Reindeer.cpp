/*
 * author:  Alexander Grill
 * file:    Reindeer.cpp
 * project: santa_claus_problem
 * date:    01.01.2021
*/

//includes
#include "Reindeer.h"
#include "utils.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

#include "rang.hpp"

#include <thread>
#include <iostream>

//namespaces
using namespace std;
using namespace rang;

//Methoden Definitionen

/*
-Name:
-Beschreibung:
-Input: 
-Output:        
*/
void Reindeer::comeback(){
    unique_lock<std::mutex> ulr{mxr};
    while (christmas == false && sc->get_readytofly() == false)
    {
        int t = get_randomnum(0.5, 1.5) * 1000;
        this_thread::sleep_for(std::chrono::milliseconds(t));
        reindeer += 1;
        cout << fg::blue << reindeer << " Reindeer are in the stable\n" << flush;
        spdlog::get("console")->info("A Reindeer is back");
        if (reindeer == maxreindeer && christmas == true){
            sc->set_doaction();
            sc->santaSem.notify_one();
        }
        if (reindeerSem.wait_for(ulr, 1s, [&] { return sc->get_readytofly() == true; })){
            get_Hitched();
        }
    }
    if (christmas == true)
    {
        sc->set_doaction();
        sc->santaSem.notify_one();
    }
}

/*
-Name:
-Beschreibung:
-Input: 
-Output:        
*/
void Reindeer::get_Hitched(){
    cout << fg::yellow << "Reindeers are hichted by Santa\n" << flush;
    this_thread::sleep_for(3s);
    cout << fg::green << "Santa we can fly\n" << flush;
    cout << fg::green << "Merry Christmas Ho Ho Ho\n" << flush;
}

/*
-Name:
-Beschreibung:
-Input: 
-Output:        
*/
int Reindeer::get_Reindeer(){
    return reindeer;
}

/*
-Name:
-Beschreibung:
-Input: 
-Output:        
*/
int Reindeer::get_MaxReindeer(){
    return maxreindeer;
}

/*
-Name:
-Beschreibung:
-Input: 
-Output:        
*/
void Reindeer::set_Santa(SantaClaus* s){
    sc = s;
}

/*
-Name:
-Beschreibung:
-Input: 
-Output:        
*/
void Reindeer::reset_Reindeer(){
    reindeer = 0;
}