cmake_minimum_required(VERSION 3.27.7)
project(main)

set(CMAKE_CXX_STANDARD 20)

add_executable(main main.cpp
        BoatRoute.cpp
        BoatRoute.h
        Passenger.cpp
        Passenger.h
        Boat.cpp
        Boat.h)
