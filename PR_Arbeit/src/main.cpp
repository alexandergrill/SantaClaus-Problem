/*
 * author:  Alexander Grill
 * file:    main.cpp
 * project: santa_claus_problem
 * date:    28.11.2020
*/

#include "include/CLI11.hpp"
#include <iostream>
#include <thread>
#include <condition_variable>
#include <mutex>

using namespace std;

class SantaClaus{
private:
    int elves{0};
    int reindeer{0};
    condition_variable santaSem;
    condition_variable reindeerSem;
public:
    SantaClaus();
    void operator()(){

    }
};

class Reindeers{
private:
    SantaClaus* santa;
    mutex mx;
public:
    Reindeers(SantaClaus* s){
        santa = s;
    }
    void operator()(){

    }
};

int main(int argc, char *argv[]){


}