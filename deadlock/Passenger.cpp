#include "Passenger.h"

Passenger::Passenger(const unsigned id) : id(id) {}

Passenger::~Passenger() = default;

void Passenger::load(const unsigned boatId) const {
    cout << "Passenger " << id << " is loaded to boat " << boatId << endl;
}

void Passenger::unload(const unsigned boatId) const {
    cout << "Passenger " << id << " is unloaded from boat " << boatId << endl;
}
