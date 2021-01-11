/*
 * author:  Alexander Grill
 * file:    utils.cpp
 * project: santa_claus_problem
 * date:    01.01.2021
*/

#include "utils.h"
#include "rang.hpp"

#include <random>

using namespace std;
using namespace rang;

double get_randomnum(double start, double end){
    random_device rd;
    mt19937 gen{rd()};
    uniform_real_distribution<> dis{start, end};
    double num = dis(gen);
    return num;
}

void to_christmas(int hours){
    christmas = false;
    for (int i = 0; i < hours; i++){
        sleep(1);
    }
    christmas = true;
}
