/*
 * author:  Alexander Grill
 * file:    Elves.h
 * project: santa_claus_problem
 * date:    01.01.2021
*/

#ifndef ELVES_H
#define ELVES_H

//includes
#include "SantaClaus.h"

#include <mutex>
#include <condition_variable>

//forward declaration
class SantaClaus;

//Klasse Elfen
class Elves{
private:
//Variablen
    SantaClaus *sc;     //Verweis auf das dazugehörige SantaClaus Objekt
    std::mutex &mxe;    //Mutex Obekt
    int elves{0};       //Elfen
    int maxelves{0};    //Elfen die benötigt werden um Santa zu wecken
    int elvessum{0};    //alle Elfen die Hilfe benötigten 
public:
//Condition Variable
    std::condition_variable elfTex;
//Konstruktor
    Elves(int me, std::mutex& xe):mxe{xe}{
        maxelves = me;
    }
//Methoden
    void tinker();
    void get_Help();
    int get_Elves();
    int get_MaxElves();
    int get_SumElves();
    void set_Santa(SantaClaus *s);
};

#endif