/*
 * author:  Alexander Grill
 * file:    utils.h
 * project: santa_claus_problem
 * date:    01.01.2021
*/

#ifndef UTILS_H
#define UTILS_H

#include "SantaClaus.h"
#include "Elves.h"
#include "Reindeer.h"

#include <iostream>


extern bool christmas;

double get_randomnum(double start, double end);
void to_christmas(int hours);
void write_intoJSON(SantaClaus* sc, Elves *ev, Reindeer* rn, std::string json_file);

#endif