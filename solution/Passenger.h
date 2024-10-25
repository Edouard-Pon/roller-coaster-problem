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

    void load(unsigned boatId) const;
    void unload(unsigned boatId) const;
};



#endif //PASSENGER_H
