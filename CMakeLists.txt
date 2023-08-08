cmake_minimum_required(VERSION 3.23)
project(ParkingSystem C)

set(CMAKE_C_STANDARD 99)

add_executable(ParkingSystem main.c parking.c cmake-build-debug/parking.h)
