#include "Boat.h"
#include "BoatRoute.h"


Boat::Boat(const unsigned id, const unsigned capacity, BoatRoute &boatRoute)
    : id(id), boatCapacity(capacity), boatRoute(boatRoute) {}

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
    cout << "Boat " << this->id << " is loading passengers" << endl;
    while (this->passengers.size() < boatCapacity && !passengers.empty()) {
        this->passengers.push_back(passengers.back());
        passengers.back().load(this->id);
        passengers.pop_back();
    }
    if (this->passengers.size() == boatCapacity) {
        cout << "Boat " << this->id << " is full" << endl;
        cout << this->passengers.size() << " passengers are loaded" << endl;
        cvLoad.notify_one();
    }
}

void Boat::unloadPassengers(vector<Passenger> &passengers, unsigned &currentDockBoat) {
    cout << "Boat " << this->id << " is unloading passengers" << endl;
    while (!this->passengers.empty()) {
        passengers.push_back(this->passengers.back());
        this->passengers.back().unload(this->id);
        this->passengers.pop_back();
    }
}

void Boat::run() {
    unique_lock<mutex> lock(mtx);
    cvLoad.wait(lock, [this] { return this->passengers.size() == boatCapacity; });
    isRunning = true;
    cout << "Boat " << this->id << " is running" << endl;
    boatRoute.notifyNextBoat();
    this_thread::sleep_for(chrono::seconds(1));
    isRunning = false;
    cvUnload.notify_one();
}

void Boat::start(vector<Passenger> &passengers, unsigned &currentDockBoat) {
    thread([this, &passengers, &currentDockBoat] {
        loadPassengers(passengers);
        run();
        unique_lock<mutex> lock(mtx);
        cvUnload.wait(lock, [this, &currentDockBoat] { return !isRunning && currentDockBoat == this->id; });
        unloadPassengers(passengers, currentDockBoat);
    }).detach();
}

bool Boat::isBoatRunning() const {
    return isRunning;
}
