#include "Boat.h"
#include "BoatRoute.h"
#include <iostream>
#include <thread>


Boat::Boat(unsigned id, unsigned capacity, BoatRoute &boatRoute, condition_variable &cvLoad, condition_variable &cvUnload)
    : id(id), boatCapacity(capacity), boatRoute(boatRoute), cvLoad(cvLoad), cvUnload(cvUnload) {}

Boat::~Boat() {
    passengers.clear();
}

void Boat::setBoatCapacity(const unsigned capacity) {
    boatCapacity = capacity;
}

unsigned Boat::getBoatCapacity() const {
    return boatCapacity;
}

unsigned Boat::getId() const {
    return id;
}

void Boat::loadPassengers(vector<Passenger> &passengers) {
    unique_lock<mutex> lock(mtx);

    while (this->passengers.size() < boatCapacity) {
        while (!passengers.empty() && this->passengers.size() < boatCapacity) {
            this->passengers.push_back(passengers.back());
            passengers.back().load(this->id);
            passengers.pop_back();
        }

        if (this->passengers.size() < boatCapacity) {
            cvLoad.wait(lock, [this, &passengers] { return !passengers.empty(); });
        }
    }

    cout << "Boat " << this->id << " is full" << endl;
    cout << this->passengers.size() << " passengers are loaded" << endl;
    cvLoad.notify_all();
}

void Boat::unloadPassengers(vector<Passenger> &passengers) {
    cout << "Boat " << this->id << " is unloading passengers" << endl;
    while (!this->passengers.empty()) {
        passengers.push_back(this->passengers.back());
        this->passengers.back().unload(this->id);
        this->passengers.pop_back();
    }
    boatRoute.moveBoatToLoad(this);
    boatRoute.notifyLoad();
}

void Boat::run() {
    unique_lock<mutex> lock(mtx);
    cvLoad.wait(lock, [this] { return this->passengers.size() == boatCapacity; });
    isRunning = true;
    cout << "Boat " << this->id << " is running" << endl;
    boatRoute.moveBoatToUnload(this);
    boatRoute.notifyNextBoat();
    this_thread::sleep_for(chrono::seconds(1));
    isRunning = false;
    cvUnload.notify_one();
}

void Boat::start(vector<Passenger> &passengers) {
    thread([this, &passengers] {
        loadPassengers(passengers);
        run();
        unique_lock<mutex> lock(mtx);
        cvUnload.wait(lock, [this] { return !isRunning; });
        unloadPassengers(passengers);
    }).detach();
}

bool Boat::isBoatRunning() const {
    return isRunning;
}
