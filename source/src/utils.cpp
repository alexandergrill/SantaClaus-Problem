/*
 * author:  Alexander Grill
 * file:    utils.cpp
 * project: santa_claus_problem
 * date:    01.01.2021
*/

//includes
#include "utils.h"

#include <rang/rang.hpp>
#include <json/json.hpp>
#include <tabulate/table.hpp>

#include <random>
#include <iostream>
#include <fstream>

//namespaces
using namespace std;
using namespace rang;
using namespace tabulate;
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
        sleep(1);
    }
    christmas = true;
}

/*
-Name: void write_IntoJSON
-Beschreibung: schreibt alle Objekt Daten in ein json file
-Input: SantaClaus *sc, Elves *ev, Reindeer *rn, string json_file
-Output:
*/
void write_IntoJSON(SantaClaus *sc, Elves *ev, Reindeer *rn, std::string json_file){
    json data;
    ofstream of(json_file);
    double btime = sc->get_Blithelytime();
    int esum = ev->get_SumElves();
    int rsum = rn->get_Reindeer();

    data["Santa Claus"]["Blithely Hours"] = btime;
    data["Reindeer"]["In Stable"] = rsum;
    data["Elves"]["Hellped Elves"] = esum;
    of << data;
}

/*
-Name: void write_IntoJSON
-Beschreibung: printed Objekt Information in Form einer Tabelle in der Console
-Input: SantaClaus *sc, Elves *ev, Reindeer *rn
-Output:
*/
void print_Table(SantaClaus *sc, Elves *ev, Reindeer *rn){
    Table objects_table;
    double btime = sc->get_Blithelytime();
    int esum = ev->get_SumElves();
    int rsum = rn->get_Reindeer();

    //objects_table.format().font_style({tabulate::FontStyle::arial}).width(30);
    objects_table.add_row({"Santa Claus", "Elves", "Reindeer"});
    objects_table.add_row({to_string(btime), to_string(esum), to_string(rsum)});
    cout << objects_table << endl;
}