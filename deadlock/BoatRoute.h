#ifndef BOATROUTE_H
#define BOATROUTE_H

#include <iostream>
#include <vector>
#include <memory>
#include <mutex>
#include <condition_variable>
#include "Boat.h"
#include "Passenger.h"
#include <thread>

using namespace std;

class BoatRoute {
private:
    unsigned dockBoatsCapacity = 1;
    unsigned currentDockBoat = 0;
    vector<unique_ptr<Boat>> boats;
    vector<Passenger> passengers;
    mutex mtx;
    condition_variable cv;
    condition_variable cvNextBoat;

public:
    BoatRoute();
    ~BoatRoute();
    void run();
    void init(unsigned boatsCount, unsigned passengersCount, unsigned boatCapacity);
    void nextBoat();
    void notifyNextBoat();
    unsigned getCurrentDockBoat() const;
};

#endif //BOATROUTE_H
