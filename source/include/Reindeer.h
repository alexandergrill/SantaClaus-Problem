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

class Reindeer{
private:
    int reindeer{0};
    SantaClaus &sc;
    std::mutex& mxr;
    std::condition_variable reindeerSem;
public:
    Reindeer(SantaClaus s,std::mutex& xr):sc{s}, mxr{xr}{
    }
    void comeback();
    int getReindeer();
    void resetReindeer();
    void getHitched();
};

#endif