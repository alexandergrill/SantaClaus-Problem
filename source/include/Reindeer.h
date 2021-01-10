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

class SantaClaus;

class Reindeer{
private:
    int reindeer{0};
    SantaClaus* sc;
    std::mutex& mxr;
    std::mutex r;
public:
    std::condition_variable reindeerSem;
    Reindeer(std::mutex& xr):mxr{xr}{
    }
    void comeback();
    void set_Santa(SantaClaus *s);
    int get_Reindeer();
    void get_Hitched();
    void reset_Reindeer();
};

#endif