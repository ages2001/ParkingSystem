#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

#define STR_LIMIT 100
#define PARK_LIMIT 1000

typedef struct Vehicle {
    char *plate;
    int classCode;
    float weight;
    int minuteInParking;
    char *driverNameSurname;
    char *specificStateOfDriver;
    int discountRate;
    float parkingFee;
} Vehicle;

typedef struct VehicleArray {
    Vehicle **vehicles;
    size_t size;
} VehicleArray;

void clearVehicleArray(VehicleArray *vehicleList);

void printVehicleInfo(Vehicle vehicle);

char *returnClassName(int classCode);

bool isSpecificState(char *specificStateOfDriver);

void calculateParkingFee(Vehicle *vehicle);

int countOfClassName(VehicleArray vehicleArray, int classCode);

float totalRevenue(VehicleArray vehicleArray);

float totalRevenueForClassName(VehicleArray vehicleArray, int classCode);

int averageMinuteForClassName(VehicleArray vehicleArray, int classCode);

int lightCarCount(VehicleArray vehicleArray);

float heavyBusTruckLorryRatio(VehicleArray vehicleArray);

float shortMotorCycleCarRatio(VehicleArray vehicleArray);

float longMinibusBusRatio(VehicleArray vehicleArray);

float longWorthyVehicles(VehicleArray vehicleArray);

int specStateVehicleCount(VehicleArray vehicleArray, int specCode);

int averageMinuteForSpecVehicles(VehicleArray vehicleArray, int specCode);

float longDiscountedVehicleCount(VehicleArray vehicleArray);

Vehicle *longestVehicle(VehicleArray vehicleArray);

Vehicle *worthiestCar(VehicleArray vehicleArray);
