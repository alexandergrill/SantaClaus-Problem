/*
 * author:  Alexander Grill
 * file:    Elves.cpp
 * project: santa_claus_problem
 * date:    01.01.2021
*/

//includes
#include "Elves.h"
#include "utils.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

#include <rang/rang.hpp>

#include <thread>
#include <random>
#include <iostream>

//namespaces
using namespace std;
using namespace rang;

//Methoden Definitionen

/*
-Name: void tinker
-Beschreibung: Arbeitsablauf der Elfen, Santa wird geweckt wenn Elfen in benötigen
-Input: 
-Output:        
*/
void Elves::tinker(){
    unique_lock<mutex> ulh{mxe};
    while (sc->get_Readytofly() == false && christmas == false){
        if (elves != maxelves){
            int t = get_RandomNum(0.5, 1.0) * 1000;
            this_thread::sleep_for(chrono::milliseconds(t));
            elves += 1;
            elvessum += 1;
            cout << fg::cyan << elves << " Elves need help\n" << flush;
            spdlog::get("console")->info("A Elve is waiting for Santa´s Help");
        }
        if (elfTex.wait_for(ulh, 1s, [&] { return sc->get_Readytohelp() == true; })){
            if(sc->get_Readytofly() == false){
                get_Help();
                elves = 0;
                cout << fg::magenta << "Santa go sleep!\n" << flush;
            }
       }
       if (elves == maxelves && christmas == false){
           sc->set_Doaction();
           sc->santaSem.notify_one();
       }
    }
}

/*
-Name: void get_Help
-Beschreibung: Santa Claus hilft jeden einzelnen Elfen
-Input:
-Output:        
*/
void Elves::get_Help(){
    double totaltime{0.00};
    while (elves > 0){
        int t = get_RandomNum(0.5, 1.0) * 1000;
        totaltime += t / 1000.0;
        this_thread::sleep_for(chrono::milliseconds(t));
        cout << fg::cyan << (elves - (maxelves + 1)) * -1 << " elves helped\n"<< flush;
        elves -= 1;
    }
    sc->set_Blithelytime(totaltime);
    sc->set_Readytohelp();
}

/*
-Name: int get_Elves
-Beschreibung: gibt die Anzahl der Elfen zurück, die Hilfe brauchen
-Input:
-Output: int elves     
*/
int Elves::get_Elves(){
    return elves;
}

/*
-Name: int get_MaxElves
-Beschreibung: gibt die Maximale Anzahl der Elfen zurück, die benötigt werden um Santa zu wecken
-Input:
-Output: int maxelves     
*/
int Elves::get_MaxElves()
{
    return maxelves;
}

/*
-Name: int get_SumElves
-Beschreibung: gibt die Summe der Elfen zurück, die Hilfe brauchten
-Input:
-Output: int elvessum    
*/
int Elves::get_SumElves(){
    return elvessum;
}

/*
-Name: void set_Santa
-Beschreibung: setzt den Verweis, auf das jeweilige SantaClaus Objekt
-Input: SantaClaus* s
-Output:        
*/
void Elves::set_Santa(SantaClaus* s){
    sc = s;
}