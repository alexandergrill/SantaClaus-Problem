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

//Klasse Elven
class Elves{
private:
//Variablen
    int elves{0};       //Elfen
    int elvessum{0};    //alle Elfen die Hilfe benötigten
    std::mutex& mxe;    //Mutex Obekt
    SantaClaus* sc;     //Verweis auf das dazugehörige SantaClaus Objekt 
public:
//Condition Variable
    std::condition_variable elfTex;
//Konstruktor
    Elves(std::mutex& xe):mxe{xe}{
    }
//Methoden
    void tinker();
    void get_Help();
    int get_Elves();
    int get_SumElves();
    void set_Santa(SantaClaus *s);

};

#endif