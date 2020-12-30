/*
 * author:  Alexander Grill
 * file:    main.cpp
 * project: santa_claus_problem
 * date:    28.11.2020
*/

#include "include/CLI11.hpp"
#include <iostream>
#include <thread>
#include <condition_variable>
#include <mutex>
#include <random>
#include <chrono>

using namespace std;

std::condition_variable santaSem;
std::condition_variable reindeerSem;
std::mutex mx;



class SantaClaus{
private:
    int reindeer{0};

public:
    SantaClaus(){

    }
    void operator()(){
        while(true){
            unique_lock<mutex> ul{mx};
            reindeerSem.wait(ul, [] { return (reindeer != 9) ? true : false; });
            if(reindeer < 9 ){
                cout << "The reindeers are not enough to fly only " << reindeer << "\n" << flush;
            }
            if(reindeer == 9){
                cout << "Start\n" << flush;
            }
            this_thread::sleep_for(2s);
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
            random_device rd;
            mt19937 gen{rd()};
            uniform_real_distribution<> dis{1, 5};
            double time = dis(gen);
            int t = time * 1000;
            this_thread::sleep_for(chrono::milliseconds(t));
            lock_guard<mutex> lg(mx);
            cout << "Additional Reindeer is ready\n" << flush;
            santa->addReindeer();
            if(santa->getReindeer() == 9){
                cout << "Santa Claus we can drive\n" << flush;
                reindeerSem.notify_one();
                break;
            }
        }

    }
};

int main(int argc, char *argv[]){
    SantaClaus sc;
    Reindeers rs(&sc);

    thread tsanta{sc};
    thread treindeers{rs};

    tsanta.join(),
    treindeers.join();
}