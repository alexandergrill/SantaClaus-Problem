/*
 * author:  Alexander Grill
 * file:    main.cpp
 * project: santa_claus_problem
 * date:    01.01.2021
*/

//includes
#include "Reindeer.h"
#include "Elves.h"
#include "SantaClaus.h"
#include "utils.h"

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

#include <rang/rang.hpp>
#include <CLI11/CLI11.hpp>


#include <thread>
#include <mutex>


//namespaces
using namespace std;
using namespace rang;


//Variable
bool christmas;

int main(int argc, char *argv[]){
    int reendiernum{9};                     //maximale Zahl der Rentier, um Santa zu wecken
    int elvesnum{3};                        //maximale Zahl der Elfen, um Santa zu wecken
    int time{24};                           //Anzahl der Stunden bis zu Christmas
    string jsonfilepath;                    //json Filename
    bool display_table{false};              //wird auf true gesetzt wenn am Ende Tabelle geprinted werden soll
//Kommandozeilenparameter
    CLI::App app("Santa Claus Problem");
    app.add_option("-r,--r", reendiernum, "number of reindeer, which will be needed to fly")->check([](const string &str) {
        auto check = str.find_first_not_of("0123456789");
        if (check == string::npos){
            return string();
        }
        else{
            return string(str + " contains not numeric character");
        }
    });
    app.add_option("-e,--e", elvesnum, "number of elves, that work in the factory")->check([](const string &str) {
        auto check = str.find_first_not_of("0123456789");
        if (check == string::npos){
            return string();
        }
        else{
            return string(str + " contains not numeric character");
        }
    });
    app.add_option("-t,--t", time, "number of hours until christmas")->check([](const string &str) {
        auto check = str.find_first_not_of("0123456789");
        if (check == string::npos){
            return string();
        }
        else{
            return string(str + " contains not numeric character");
        }
    });
    app.add_option("-j,--j", jsonfilepath, "write santa, reindeer, elves details in json File")->check(CLI::ExistingFile);
    app.add_flag("-d,--d", display_table, "show you a table about the Objects Santa, Elves, Reindeer");
    CLI11_PARSE(app, argc, argv);

    auto console = spdlog::stderr_color_mt("console");
    console->set_level(spdlog::level::trace);

    mutex mx;                               //Mutex Objekt

    Elves ev(elvesnum, ref(mx));            //Objekt Elfen
    Reindeer rs(reendiernum, ref(mx));      //Objekt Rentier
    SantaClaus sc(ev,rs, ref(mx));          //Objekt SantaClaus
    ev.set_Santa(&sc);                      //Santaobjekt wird gesetzt
    rs.set_Santa(&sc);                      //Santaobjekt wird gesetzt

    thread (to_Christmas, time).detach();   //Thread to_christmas
    thread tsanta([&]{sc.sleep();});        //Thread santa sleep
    thread treindeer([&]{rs.comeback();});  //Thread reindeer comebock
    thread telves([&]{ev.tinker();});       //Thread elves tinker

//zum Schluss werden alle Threads gejoint
    telves.join();                           
    tsanta.join(),
    treindeer.join();

//Ausgabe wenn Christmas vorüber ist
    if (christmas == true && sc.get_Readytofly() == false){
        cerr << fg::red << "Christmas is over!\n"
             << flush;
        spdlog::get("console")->warn("The children do not get their presents at the right time");
    }

//wenn die Variable auf true gesetzt wird wird die Tabelle in der Console ausgegeben
    if (display_table == true){
        print_Table(&sc, &ev, &rs);
    }

//Schreibt Objektdaten in json file
    if (jsonfilepath.empty() == false){
        write_IntoJSON(&sc, &ev, &rs, jsonfilepath);
    }
}