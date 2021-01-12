/*
 * author:  Alexander Grill
 * file:    SantaClaus.h
 * project: santa_claus_problem
 * date:    01.01.2021
*/

#ifndef SANTACLAUS_H
#define SANTACLAUS_H

//includes
#include "Reindeer.h"
#include "Elves.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"


#include <mutex>
#include <condition_variable>

//forward declaration
class Elves;
class Reindeer;

//Klasse SantaClaus
class SantaClaus{
private:
//Variablen
    Elves &elv;                 //Verweis auf das dazugehörige Elven Objekt
    Reindeer &ren;              //Verweis auf das dazugehörige Renntier Objekt
    std::mutex &mxs;            //Mutex Obekt
    double blithelytime{0};     //gesamte Schlafzeit
    bool doaction{false};       //bool Variable, für santaSem.wait
    bool readytofly{false};     //bool Variable, für ren.reindeerSem.notify_one       
    bool readytohelp{false};    //bool Variable, für elv.elfTex.notify_one
public:
//Condition Variable
    std::condition_variable santaSem;
//Konstruktor
    SantaClaus(Elves& e, Reindeer& r, std::mutex& xs): elv{e}, ren{r}, mxs{xs}{
    }
//Methoden
    void sleep();
    int get_Blithelytime();
    bool get_Readytofly();
    bool get_Readytohelp();
    void set_Blithelytime(double t);
    void set_Readytohelp();
    void set_Doaction();
};

#endif