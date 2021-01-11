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
    int reindeer{0};        //Renntiere
    int maxreindeer;        //Renntiere die benötigt werden um Santa zu wecken
    std::mutex& mxr;        //Mutex Objekt
     SantaClaus* sc;         //Verweis auf das dazugehörige SantaClaus Objekt
public:
//Condition Variable
    std::condition_variable reindeerSem;
//Konstruktor
    Reindeer(int rmax, std::mutex& xr):maxreindeer{rmax}, mxr{xr}{
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