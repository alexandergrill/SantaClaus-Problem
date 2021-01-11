/*
 * author:  Alexander Grill
 * file:    Reindeers.h
 * project: santa_claus_problem
 * date:    01.01.2021
*/

#ifndef REINDEER_H
#define REINDEER_H

#include "SantaClaus.h"

#include <mutex>
#include <condition_variable>

//forward declaration
class SantaClaus;

// Renntier Klasse
class Reindeer{
private:
//Variablen
    int reindeer{0};        //Renntiere
    int maxreindeer;        //Renntiere die benötigt werden um Santa zu wecken
    SantaClaus* sc;         //das dazugehörige SantaClaus Objekt
    std::mutex& mxr;        //Mutsex Objekt
public:
//Condition Variable
    std::condition_variable reindeerSem;
//Konstruktor
    Reindeer(int rmax, std::mutex& xr):maxreindeer{rmax}, mxr{xr}{
    }
//Methoden
    void comeback();
    int get_Reindeer();
    int get_MaxReindeer();
    void get_Hitched();
    void set_Santa(SantaClaus *s);
    void reset_Reindeer();
};

#endif