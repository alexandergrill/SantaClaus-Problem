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
    SantaClaus* sc;         //das dazugehörige SantaClaus Objekt
    std::mutex& mxr;        //
public:
    std::condition_variable reindeerSem;
//Konstruktor
    Reindeer(std::mutex& xr):mxr{xr}{
    }
//
    void comeback();
    void set_Santa(SantaClaus *s);
    int get_Reindeer();
    void get_Hitched();
    void reset_Reindeer();
};

#endif