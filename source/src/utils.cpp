/*
 * author:  Alexander Grill
 * file:    utils.cpp
 * project: santa_claus_problem
 * date:    01.01.2021
*/

//includes
#include "utils.h"


#include "rang.hpp"
#include "json.hpp"

#include <random>
#include <iostream>

//namespaces
using namespace std;
using namespace rang;
using json = nlohmann::json;

//Funktionen Definitionen

/*
-Name: double get_RandomNum
-Beschreibung: liefter eine Zufallszahl zurück zwischen start und end
-Input: double start, double end
-Output: double num
*/
double get_RandomNum(double start, double end){
    random_device rd;
    mt19937 gen{rd()};
    uniform_real_distribution<> dis{start, end};
    double num = dis(gen);
    return num;
}

/*
-Name: void to_Christmas
-Beschreibung: setzt die bool Variable christmas nach einer Zeit auf true
-Input: int hours
-Output:
*/
void to_Christmas(int hours){
    christmas = false;
    for (int i = 0; i < hours; i++){
        sleep(1.1);
    }
    christmas = true;
}

/*void write_intoJSON(SantaClaus &sc, Elves &ev, Reindeer &rn, std::string json_file){
    json santa;
    json elves;
    json renndeer;
}*/
