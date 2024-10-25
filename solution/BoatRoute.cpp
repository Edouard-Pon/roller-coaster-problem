#include "BoatRoute.h"

BoatRoute::BoatRoute() = default;

BoatRoute::~BoatRoute() {
    for (auto boat : loadBoats) {
        delete boat;
    }
    for (auto boat : unloadBoats) {
        delete boat;
    }
    passengers.clear();
}

void BoatRoute::init(const unsigned boatsCount, const unsigned passengersCount, const unsigned boatCapacity) {
    for (unsigned i = 0; i < boatsCount; ++i) {
        loadBoats.push_back(new Boat(i, boatCapacity, *this, cvLoad, cvUnload));
    }

    for (unsigned i = 0; i < passengersCount; ++i) {
        Passenger passenger(i);
        passengers.push_back(passenger);
    }
}

void BoatRoute::run() {
    while (true) {
        {
            unique_lock<mutex> lock(mtx);
            if (!loadBoats.empty()) {
                Boat* boat = loadBoats.front();
                thread boatThread(&Boat::start, boat, ref(passengers));
                boatThread.detach();
            }
        }
        this_thread::sleep_for(chrono::milliseconds(100));
    }
}

void BoatRoute::moveBoatToUnload(Boat* boat) {
    unique_lock<mutex> lock(mtx);
    if (!loadBoats.empty() && loadBoats.front() == boat) {
        loadBoats.erase(loadBoats.begin());
        unloadBoats.push_back(boat);
        cout << "Boat " << boat->getId() << " is moving to unload queue" << endl;
    }
}

void BoatRoute::moveBoatToLoad(Boat* boat) {
    unique_lock<mutex> lock(mtx);
    if (!unloadBoats.empty() && unloadBoats.front() == boat) {
        unloadBoats.erase(unloadBoats.begin());
        loadBoats.push_back(boat);
        cout << "Boat " << boat->getId() << " is moving to load queue" << endl;
    }
}

void BoatRoute::notifyNextBoat() {
    cvNextBoat.notify_one();
}

void BoatRoute::notifyLoad() {
    cvLoad.notify_all();
}
