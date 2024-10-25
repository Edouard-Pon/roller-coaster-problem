#include <iostream>
#include "BoatRoute.h"

int main() {
    BoatRoute boatRoute;
    unsigned boatsCount = 2;
    unsigned passengersCount = 9; // 9 - deadlock ; 10 - no deadlock
    unsigned boatCapacity = 5;

    boatRoute.init(boatsCount, passengersCount, boatCapacity);
    boatRoute.run();

    return 0;
}

