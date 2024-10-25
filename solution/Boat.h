#ifndef BOAT_H
#define BOAT_H

#include <vector>
#include <mutex>
#include <condition_variable>
#include "Passenger.h"

using namespace std;

class BoatRoute;

class Boat {
public:
    Boat(unsigned id, unsigned capacity, BoatRoute &boatRoute, condition_variable &cvLoad, condition_variable &cvUnload);
    ~Boat();
    void setBoatCapacity(unsigned capacity);
    unsigned getBoatCapacity() const;
    unsigned getId() const;
    void loadPassengers(vector<Passenger> &passengers);
    void unloadPassengers(vector<Passenger> &passengers);
    void run();
    void start(vector<Passenger> &passengers);
    bool isBoatRunning() const;

private:
    unsigned id;
    unsigned boatCapacity;
    vector<Passenger> passengers;
    bool isRunning = false;
    mutex mtx;
    condition_variable &cvLoad;
    condition_variable &cvUnload;
    BoatRoute &boatRoute;
};


#endif //BOAT_H
