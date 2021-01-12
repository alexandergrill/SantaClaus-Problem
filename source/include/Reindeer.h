/*
 * author:  Alexander Grill
 * file:    Reindeers.h
 * project: santa_claus_problem
 * date:    01.01.2021
*/

#ifndef REINDEER_H
#define REINDEER_H

//includes
#include "SantaClaus.h"

#include <mutex>
#include <condition_variable>

//forward declaration
class SantaClaus;

//Klasse Renntiere
class Reindeer{
private:
//Variablen
    SantaClaus *sc;         //Verweis auf das dazugehörige SantaClaus Objekt
    std::mutex &mxr;        //Mutex Objekt
    int reindeer{0};        //Rentiere
    int maxreindeer;        //Rentiere die benötigt werden um Santa zu wecken
public:
//Condition Variable
    std::condition_variable reindeerSem;
//Konstruktor
    Reindeer(int mr, std::mutex& xr):mxr{xr}{
        maxreindeer = mr;
    }    
//Methoden
    void comeback();
    void get_Hitched();
    int get_Reindeer();
    int get_MaxReindeer();
    void set_Santa(SantaClaus *s);
    void reset_Reindeer();
};

#endif