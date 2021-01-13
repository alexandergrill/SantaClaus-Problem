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

#include <rang/rang.hpp>

#include <thread>
#include <iostream>

//namespaces
using namespace std;
using namespace rang;

//Methoden Definitionen

/*
-Name: void comeback
-Beschreibung: Rückkunft aller Rentiere aus dem Osten
-Input: 
-Output:        
*/
void Reindeer::comeback(){
    while (christmas == false && sc->get_Readytofly() == false){
        int t = get_RandomNum(1.0, 2.0) * 1000;
        this_thread::sleep_for(std::chrono::milliseconds(t));
        reindeer += 1;
        cout << fg::blue << reindeer << " Reindeer are in the stable\n" << flush;
        spdlog::get("console")->info("A Reindeer is back");
        if(reindeer == maxreindeer){
            sc->set_Doaction();
            sc->santaSem.notify_one();
        }
        unique_lock<std::mutex> ulr{mxr};
        if (reindeerSem.wait_for(ulr, 1s, [&] { return sc->get_Readytofly() == true; })){
            get_Hitched();
        }
    }
    if (christmas == true){
        sc->set_Doaction();
        sc->santaSem.notify_one();
    }
}

/*
-Name: void get_Hitched
-Beschreibung: wenn alle Rentiere da sind, werden sie vom Santa an den Schlitten angehängt
-Input: 
-Output:        
*/
void Reindeer::get_Hitched(){
    cout << fg::yellow << "Reindeers are hichted by Santa\n" << flush;
    this_thread::sleep_for(3s);
    cout << fg::green << "Santa we can fly\n" << flush;
    spdlog::get("console")->info("The children get their presents at the right time");
    cout << fg::green << "Merry Christmas Ho Ho Ho\n" << flush;
}

/*
-Name: int get_Reindeer
-Beschreibung: gibt die Anzahl der Rentier zurück, die zurückgekommen sind
-Input: 
-Output: int reindeer     
*/
int Reindeer::get_Reindeer(){
    return reindeer;
}

/*
-Name: int get_MaxReindeer
-Beschreibung: gibt die maximale Anzahl der Rentier zurück, die benötigt werden um Santa zu wecken
-Input: 
-Output: int maxreindeer
*/
int Reindeer::get_MaxReindeer(){
    return maxreindeer;
}

/*
-Name: void set_Santa
-Beschreibung: setzt den Verweis, auf das jeweilige SantaClaus Objekt
-Input: SantaClaus* s
-Output:        
*/
void Reindeer::set_Santa(SantaClaus* s){
    sc = s;
}

/*
-Name: void reset_Reindeer()
-Beschreibung: setzt die Anzahl der Renntier auf 0 ->für Debuggen notwendig gewesen
-Input: 
-Output:        
*/
void Reindeer::reset_Reindeer(){
    reindeer = 0;
}