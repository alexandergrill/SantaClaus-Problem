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
int reindeer{0};

bool hitchable() { return reindeer == 9; }

class Elves
{
private:
    int elves{0};

public:
    Elves()
    {
    }
    void operator()()
    {
        while (true)
        {
            unique_lock<mutex> ulg{mx};
            random_device rd;
            mt19937 gen{rd()};
            uniform_real_distribution<> dis{0.5, 1.0};
            double time = dis(gen);
            int t = time * 1000;
            this_thread::sleep_for(chrono::milliseconds(t));
            elves += 1;
            cout << fg::blue << elves << " need help\n" << flush;
            if (elves == 3)
            {
                santaSem.notify_one();
            }
        }
    }
    void getHelp()
    {
        while (elves < 0)
        {
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
    int getElves()
    {
        return elves;
    }
};

class SantaClaus{
private:
    Elves* elv;

public:
    SantaClaus(Elves* e){
        elv = e;
    }
    void operator()(){
        while(true){
            unique_lock<mutex> ul{mx};
            santaSem.wait(ul);
            if(reindeer < 9 ){
                cout << fg::red << "The reindeers are not enough to fly only " << reindeer << "\n" << flush;
            }
            if(reindeer == 9){
                cout << "Start\n" << flush;
                reindeerSem.notify_one();
                reindeer -= 9;
            }
            if(elv->getElves() == 3){
                elv->getHelp();
            }

            this_thread::sleep_for(3s);
        }
    }
    void addReindeer(){
        reindeer += 1;
    }

    int getReindeer(){
        return reindeer;
    }
};

class Reindeers{
private:
    SantaClaus* santa;

public:
    Reindeers(SantaClaus* s){
        santa = s;
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
            santa->addReindeer();
           
            if(santa->getReindeer() == 9){
                santaSem.notify_one();
            }
            ulg.unlock();
            //reindeerSem.wait(ulg, hitchable);
            //cout << "we can fly" << endl;
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
    SantaClaus sc(&ev);
    Reindeers rs(&sc);

    thread tsanta{sc};
    thread treindeers{rs};

    tsanta.join(),
    treindeers.join();
}