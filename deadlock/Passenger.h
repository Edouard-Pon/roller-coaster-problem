#ifndef PASSENGER_H
#define PASSENGER_H

#include <iostream>

using namespace std;

class Passenger {
private:
    const unsigned id;

public:
    explicit Passenger(unsigned id);
    ~Passenger();

    void load(const unsigned boatId) const;
    void unload(const unsigned boatId) const;
};


#endif //PASSENGER_H
