#ifndef BOATROUTE_H
#define BOATROUTE_H

#include <vector>
#include <mutex>
#include <condition_variable>
#include "Boat.h"
#include "Passenger.h"
#include <thread>

using namespace std;

class BoatRoute {
private:
    unsigned dockBoatsCapacity = 1;
    vector<Boat*> loadBoats;
    vector<Boat*> unloadBoats;
    vector<Passenger> passengers;
    mutex mtx;
    condition_variable cvNextBoat;
    condition_variable cvLoad;
    condition_variable cvUnload;

public:
    BoatRoute();
    ~BoatRoute();
    void run();
    void init(unsigned boatsCount, unsigned passengersCount, unsigned boatCapacity);
    void notifyNextBoat();
    void moveBoatToUnload(Boat* boat);
    void moveBoatToLoad(Boat* boat);
    condition_variable cv;
    void notifyLoad();
};

#endif //BOATROUTE_H
