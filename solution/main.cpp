#include <iostream>
#include "BoatRoute.h"

int main() {
    BoatRoute boatRoute;
    unsigned boatsCount = 3;
    unsigned passengersCount = 15;
    unsigned boatCapacity = 5;

    boatRoute.init(boatsCount, passengersCount, boatCapacity);
    boatRoute.run();

    return 0;
}
