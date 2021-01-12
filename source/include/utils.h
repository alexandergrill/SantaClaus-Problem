/*
 * author:  Alexander Grill
 * file:    utils.h
 * project: santa_claus_problem
 * date:    01.01.2021
*/

#ifndef UTILS_H
#define UTILS_H

//includes
#include "SantaClaus.h"
#include "Elves.h"
#include "Reindeer.h"

#include <iostream>

//Variablen
extern bool christmas;      //bool Variable->true, wenn Stunden bis Christmas abgelaufen sind

//Funktionen
double get_RandomNum(double start, double end);
void to_Christmas(int hours);
//void write_intoJSON(SantaClaus& sc, Elves& ev, Reindeer& rn, std::string json_file);

#endif