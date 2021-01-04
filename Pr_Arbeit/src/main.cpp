/*
 * author:  Alexander Grill
 * file:    main.cpp
 * project: santa_claus_problem
 * date:    28.11.2020
*/

#include "CLI11.hpp"
#include "rang.hpp"
#include "tabulate.hpp"
#include <iostream>
#include <thread>
#include <condition_variable>
#include <mutex>
#include <random>
#include <chrono>

using namespace std;
using namespace rang;
using namespace tabulate;

std::condition_variable santaSem;
std::condition_variable reindeerSem;
std::condition_variable elfTex;
std::mutex mx;
std::mutex mx2;

bool enoughtreindeer = false;
bool enoughtelves = false;
bool readytofly = false;
bool christmas = false;


void hourTOchristmas(int h){
    for(int i = 0; i < h; i++){
        mx2.lock();
        this_thread::sleep_for(1s);
        mx2.unlock();
       
    }
    christmas = true;
}


class Reindeers{
private:
    int reindeer{0};
public:
    Reindeers(){
    }
    void operator()(){
        while (readytofly == false && christmas == false){
            unique_lock<mutex> ulr{mx};
            random_device rd;
            mt19937 gen{rd()};
            uniform_real_distribution<> dis{0, 3};
            double time = dis(gen);
            int t = time * 1000;
            this_thread::sleep_for(chrono::milliseconds(t));
            reindeer += 1;
            cout << fg::yellow << reindeer << " Reindeer are in the stable\n" << flush;
            if (reindeer == 9){
                enoughtreindeer = true;
                santaSem.notify_one();
            }
            if(reindeerSem.wait_for(ulr, 3s, [&]{return readytofly == true;})){
                getHitched();
            }
        }
    }
    int getReindeer(){
        return reindeer;
    }
    void resetReindeer(){
        reindeer = 0;
    }
    void getHitched(){
        cout << fg::yellow << "Reindeers are hichted by Santa\n" << flush;
        this_thread::sleep_for(3s);
        cout << fg::green << "Santa we can fly\n" << flush;
        cout << fg::green << "Merry Christmas Ho Ho Ho\n" << flush;
    }
};

class Elves{
private:
    int elves{0};
public:
    Elves(){
    }
    void operator()(){
        while (readytofly == false && christmas == false){
            unique_lock<mutex> ulh{mx};
            random_device rd;
            mt19937 gen{rd()};
            uniform_real_distribution<> dis{0.5, 1.0};
            double time = dis(gen);
            int t = time * 1000;
            this_thread::sleep_for(chrono::milliseconds(t));
            elves += 1;
            cout << fg::blue << elves << " Elves need help\n" << flush;
            if (elves == 3){
                enoughtelves = true;
                santaSem.notify_one();
            }
        }
    }
    void getHelp(){
        while (elves < 0){
            unique_lock<mutex> ulg{mx};
            random_device rd;
            mt19937 gen{rd()};
            uniform_real_distribution<> dis{0.1, 1.5};
            double time = dis(gen);
            int t = time * 1000;
            this_thread::sleep_for(chrono::milliseconds(t));
            cout << fg::blue << (elves - 3)*-1 << " elves helped\n" << flush;
            elves -= 1;
            enoughtelves = false;
        }
    }
    int getElves(){
        return elves;
    }
};

class SantaClaus{
private:
    Elves* elv;
    Reindeers* ren;
public:
    SantaClaus(Elves* e, Reindeers* r){
        elv = e;
        ren = r; 
    }
    void operator()(){
        while (readytofly == false && christmas == false){
            unique_lock<mutex> ul{mx};
            santaSem.wait(ul, [&]() { return enoughtreindeer == true || enoughtelves == true; });
            if (ren->getReindeer() == 0){
                reindeerSem.notify_one();
                readytofly = true;
                ren->resetReindeer();
            }
            if(elv->getElves() == 3){
                elv->getHelp();
            }
        }
    }
};


int main(int argc, char *argv[]){
    int reendiernum{9};
    int elvesnum{10};
    int time{24};

    CLI::App app("Santa Claus Problem");
    app.add_flag("-r,--r", reendiernum, "number of reindeer, which will be needed to fly");
    app.add_flag("-e,--e", elvesnum, "number of elves, that work in the factory");
    app.add_flag("-t,--t", time, "number of hours until christmas");



    CLI11_PARSE(app, argc, argv);
    Elves ev;
    Reindeers rs;
    SantaClaus sc(&ev, &rs);


    thread tsanta{sc};
    thread treindeers{rs};
    thread ttime(hourTOchristmas, time);

    //thread telves{ev};

    tsanta.join(),
    treindeers.join();
    ttime.join();
    if (readytofly == false && christmas == true){
        cerr << fg::red << "Christmas is over!\n" << flush;
    }
    //telves.join();
}