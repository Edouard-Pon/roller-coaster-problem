#include "BoatRoute.h"

BoatRoute::BoatRoute() = default;

BoatRoute::~BoatRoute() {
    boats.clear();
    passengers.clear();
}

void BoatRoute::init(const unsigned boatsCount, const unsigned passengersCount, const unsigned boatCapacity) {
    for (unsigned i = 0; i < boatsCount; ++i) {
        boats.push_back(make_unique<Boat>(i, boatCapacity, *this));
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
            thread boatThread(&Boat::start, boats[currentDockBoat].get(),
                              ref(passengers), ref(currentDockBoat));
            boatThread.detach();
        }
        nextBoat();
    }
}

void BoatRoute::nextBoat() {
    unique_lock<mutex> lock(mtx);
    cvNextBoat.wait(lock);
    if (currentDockBoat == boats.size() - 1) {
        currentDockBoat = 0;
    } else {
        ++currentDockBoat;
    }
    cv.notify_all();
    cvNextBoat.notify_one();
}

void BoatRoute::notifyNextBoat() {
    cvNextBoat.notify_one();
}

unsigned BoatRoute::getCurrentDockBoat() const {
    return currentDockBoat;
}
