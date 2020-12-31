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



class Elves{
private:
    int elves{0};
public:
    Elves(){
    }
    void operator()(){
        while (true){
            unique_lock<mutex> ulg{mx};
            random_device rd;
            mt19937 gen{rd()};
            uniform_real_distribution<> dis{0.5, 1.0};
            double time = dis(gen);
            int t = time * 1000;
            this_thread::sleep_for(chrono::milliseconds(t));
            elves += 1;
            cout << fg::blue << elves << " need help\n" << flush;
            if (elves == 3){
                santaSem.notify_one();
            }
        }
    }
    void getHelp(){
        while (elves < 0){
            unique_lock<mutex> ulg{mx};
            random_device rd;
            mt19937 gen{rd()};
            uniform_real_distribution<> dis{0.1, 0.5};
            double time = dis(gen);
            int t = time * 1000;
            this_thread::sleep_for(chrono::milliseconds(t));
            cout << fg::blue << (elves - 3)*-1 << " elves helped\n" << flush;
            elves -= 1;
        }
    }
    int getElves(){
        return elves;
    }
};

class SantaClaus{
private:
    Elves* elv;
    Reindeers * ren;
public:
    SantaClaus(Elves* e, Reindeers* r){
        elv = e;
        ren = r; 
    }
    void operator()(){
        while(true){
            unique_lock<mutex> ul{mx};
            santaSem.wait(ul);
            if(ren->getReindeer() < 9 ){
                cout << fg::red << "The reindeers are not enough to fly only " << ren->getReindeer() << "\n" << flush;
            }
            if (ren->getReindeer() == 9){
                cout << "Start\n" << flush;
                reindeerSem.notify_one();
                 ren->resetReindeer();
            }
            if(elv->getElves() == 3){
                elv->getHelp();
            }
            this_thread::sleep_for(3s);
        }
    }
};

class Reindeers{
private:
    int reindeer{0};
public:
    Reindeers(){
    }
    void operator()(){
        while(true){
            unique_lock<mutex> ulg{mx};
            random_device rd;
            mt19937 gen{rd()};
            uniform_real_distribution<> dis{1, 10};
            double time = dis(gen);
            int t = time * 1000;
            this_thread::sleep_for(chrono::milliseconds(t));
           
            cout << fg::yellow << "Additional Reindeer is ready\n"<< flush;
            reindeer += 1;
           
            if(reindeer == 9){
                santaSem.notify_one();
            }
            this_thread::sleep_for(1s);
            ulg.unlock();
            //reindeerSem.wait(ulg, hitchable);
            //cout << "we can fly" << endl;
        }

    }
    int getReindeer(){
        return reindeer;
    }
    void resetReindeer(){
        reindeer = 0;
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
    thread telves{ev};

    tsanta.join(),
    treindeers.join();
    telves.join();
}