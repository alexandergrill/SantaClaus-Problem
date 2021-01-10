/*
 * author:  Alexander Grill
 * file:    main.cpp
 * project: santa_claus_problem
 * date:    01.01.2021
*/

#include "Reindeer.h"
#include "Elves.h"
#include "SantaClaus.h"

#include "rang.hpp"
#include "CLI11.hpp"

//#include "tabulate.hpp"

#include <thread>
#include <mutex>


using namespace std;

int main(int argc, char *argv[]){
    int reendiernum{9};
    int elvesnum{10};
    int time{24};

    CLI::App app("Santa Claus Problem");
    app.add_option("-r,--r", reendiernum, "number of reindeer, which will be needed to fly");
    app.add_option("-e,--e", elvesnum, "number of elves, that work in the factory");
    app.add_option("-t,--t", time, "number of hours until christmas");
    CLI11_PARSE(app, argc, argv);

    mutex mx;

    Elves ev(ref(mx));
    Reindeer rs(ref(mx));
    SantaClaus sc(ev,rs, ref(mx));
    ev.setSanta(&sc);
    rs.setSanta(&sc);

    thread tsanta([&]{sc.sleep();});
    //thread treindeers([&]{rs.comeback();});
    thread telves([&]{ev.tinker();});

    tsanta.join(),
    //treindeers.join();
    telves.join();
}


