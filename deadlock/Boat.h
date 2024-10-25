#ifndef BOAT_H
#define BOAT_H

#include <iostream>
#include <vector>
#include <mutex>
#include <condition_variable>
#include "Passenger.h"
#include <thread>

using namespace std;

class BoatRoute;

class Boat {
public:
    Boat(unsigned id, unsigned capacity, BoatRoute &boatRoute);
    ~Boat();
    void setBoatCapacity(unsigned capacity);
    unsigned getBoatCapacity() const;
    unsigned getId() const;
    void loadPassengers(vector<Passenger> &passengers);
    void unloadPassengers(vector<Passenger> &passengers, unsigned &currentDockBoat);
    void run();
    void start(vector<Passenger> &passengers, unsigned &currentDockBoat);
    bool isBoatRunning() const;
    condition_variable cvUnload;

private:
    unsigned id;
    unsigned boatCapacity;
    vector<Passenger> passengers;
    bool isRunning = false;
    mutex mtx;
    condition_variable cvLoad;
    BoatRoute &boatRoute;
};


#endif //BOAT_H
