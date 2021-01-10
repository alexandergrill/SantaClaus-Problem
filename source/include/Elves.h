/*
 * author:  Alexander Grill
 * file:    Elves.h
 * project: santa_claus_problem
 * date:    01.01.2021
*/

#ifndef ELVES_H
#define ELVES_H

#include "SantaClaus.h"

#include <mutex>
#include <condition_variable>

class SantaClaus;

class Elves{
private:
    int elves{0};
    SantaClaus* sc;
    std::mutex& mxe;


public:
    std::condition_variable elfTex;
    Elves(std::mutex& xe):mxe{xe}{
    }
    void setSanta(SantaClaus* s);
    void tinker();
    void getHelp();
    int getElves();
};

#endif