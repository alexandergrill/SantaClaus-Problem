/*
 * author:  Alexander Grill
 * file:    SantaClaus.h
 * project: santa_claus_problem
 * date:    01.01.2021
*/

#ifndef SANTACLAUS_H
#define SANTACLAUS_H

#include "Reindeer.h"
#include "Elves.h"

#include <mutex>
#include <condition_variable>

class SantaClaus{
private:
    Elves &elv;
    Reindeer &ren;
    std::mutex &mxs;
    bool enoughtreindeer{false};
    bool enoughtelves{false};
    bool readytofly{false};
public:
    std::condition_variable santaSem;
    SantaClaus(){

    }
    SantaClaus(Elves& e, Reindeer& r, std::mutex& xs): elv{e}, ren{r}, mxs{xs}{
    }

    void operator=(SantaClaus &sa){
        this->santaSem = sa.santaSem;
    }
    void sleep();
    void set_enoughtreindeer();
    void set_enoughtelves();
    bool get_readytofly();
};

#endif