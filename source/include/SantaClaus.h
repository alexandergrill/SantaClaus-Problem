/*
 * author:  Alexander Grill
 * file:    SantaClaus.h
 * project: santa_claus_problem
 * date:    01.01.2021
*/

#ifndef SANTACLAUS_H
#define SANTACLAUS_H

#include "Reindeer.h"
#include "Elves.h"

#include <mutex>
#include <condition_variable>

class Elves;
class Reindeer;

class SantaClaus{
private:
    Elves& elv;
    Reindeer& ren;
    std::mutex &mxs;
    bool doaction{false};
    bool readytofly{false};
    bool readytohelp{false};
public:
    std::condition_variable santaSem;
    SantaClaus(Elves& e, Reindeer& r, std::mutex& xs): elv{e}, ren{r}, mxs{xs}{
    }
    void sleep();
    void set_doaction();
    void set_readytohelp();
    bool get_readytofly();
    bool get_readytohelp();
};

#endif