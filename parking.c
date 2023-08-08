#include "parking.h"

void clearVehicleArray(VehicleArray *vehicleList) {
    for (size_t i = 0; i < vehicleList->size; i++) {
        free(vehicleList->vehicles[i]->plate);
        free(vehicleList->vehicles[i]->driverNameSurname);
        free(vehicleList->vehicles[i]->specificStateOfDriver);
    }
    free(vehicleList->vehicles);
}

void printVehicleInfo(Vehicle vehicle) {
    printf("\nVehicle's license plate: %s\n", vehicle.plate);
    printf("Vehicle's class name: %s\n", returnClassName(vehicle.classCode));
    printf("Vehicle's weight: %.2f kg\n", vehicle.weight);
    printf("Vehicle's time in the parking lot: %d Day %d Hour %d Minute\n",
           vehicle.minuteInParking / (24 * 60),
           vehicle.minuteInParking % (24 * 60) / 60,
           vehicle.minuteInParking % 60);
    printf("Vehicle's driver's name-surname: %s\n", vehicle.driverNameSurname);
    if (isSpecificState(vehicle.specificStateOfDriver)) {
        printf("Vehicle's driver's specific state: %s\n", vehicle.specificStateOfDriver);
        printf("Vehicle's discount rate: %d %%\n", vehicle.discountRate);
    }
    printf("Parking fee: %.2f TL", vehicle.parkingFee);
}

char *returnClassName(int classCode) {
    if (classCode == 1) return "Motorcycle";
    else if (classCode == 2) return "Car";
    else if (classCode == 3) return "Minibus";
    else if (classCode == 4) return "Bus";
    else if (classCode == 5) return "Truck";
    else return "Lorry";
}

bool isSpecificState(char *specificStateOfDriver) {
    return strcmp(specificStateOfDriver, "Veteran") == 0 || strcmp(specificStateOfDriver, "Disabled") == 0;
}

void calculateParkingFee(Vehicle *vehicle) {
    int multiplier;

    if (vehicle->minuteInParking < 60) vehicle->parkingFee = 3;
    else if (vehicle->minuteInParking >= 60 && vehicle->minuteInParking < 180) vehicle->parkingFee = 5;
    else if (vehicle->minuteInParking >= 180 && vehicle->minuteInParking < 300) vehicle->parkingFee = 7;
    else if (vehicle->minuteInParking >= 300 && vehicle->minuteInParking < 600) vehicle->parkingFee = 10;
    else if (vehicle->minuteInParking >= 600 && vehicle->minuteInParking < 1440) vehicle->parkingFee = 14;
    else vehicle->parkingFee = 15 * (int) (vehicle->minuteInParking / (24 * 60));

    if (vehicle->classCode == 1) multiplier = 1;
    else if (vehicle->classCode == 2) multiplier = 2;
    else if (vehicle->classCode == 3 || vehicle->classCode == 4) multiplier = 3;
    else multiplier = 4;

    vehicle->parkingFee *= multiplier;

    if (strcmp(vehicle->specificStateOfDriver, "Veteran") == 0) vehicle->discountRate = 100;
    else if (strcmp(vehicle->specificStateOfDriver, "Disabled") == 0) vehicle->discountRate = 50;
    else vehicle->discountRate = 0;

    vehicle->parkingFee += (float) 2.5 * (float) (vehicle->weight / 1000);

    vehicle->parkingFee -= vehicle->parkingFee * ((float) vehicle->discountRate / 100);
}

int countOfClassName(VehicleArray vehicleArray, int classCode) {
    int count = 0;
    for (size_t i = 0; i < vehicleArray.size; i++) {
        if (classCode == vehicleArray.vehicles[i]->classCode)
            count++;
    }
    return count;
}

float totalRevenue(VehicleArray vehicleArray) {
    float total = 0;
    for (size_t i = 0; i < vehicleArray.size; i++)
        total += vehicleArray.vehicles[i]->parkingFee;

    return total;
}

float totalRevenueForClassName(VehicleArray vehicleArray, int classCode) {
    float total = 0;
    for (size_t i = 0; i < vehicleArray.size; i++) {
        if (vehicleArray.vehicles[i]->classCode == classCode)
            total += vehicleArray.vehicles[i]->parkingFee;
    }

    return total;
}

int averageMinuteForClassName(VehicleArray vehicleArray, int classCode) {
    int totalForClass = 0;

    for (size_t i = 0; i < vehicleArray.size; i++) {
        if (vehicleArray.vehicles[i]->classCode == classCode)
            totalForClass += vehicleArray.vehicles[i]->minuteInParking;
    }

    return totalForClass / countOfClassName(vehicleArray, classCode);
}

int lightCarCount(VehicleArray vehicleArray) {
    int count = 0;
    for (size_t i = 0; i < vehicleArray.size; i++) {
        if (vehicleArray.vehicles[i]->weight < 1000.0 && vehicleArray.vehicles[i]->classCode == 2)
            count++;
    }

    return count;
}

float heavyBusTruckLorryRatio(VehicleArray vehicleArray) {
    int totalCount = 0, heavyCount = 0;
    for (size_t i = 0; i < vehicleArray.size; i++) {
        if (vehicleArray.vehicles[i]->classCode == 4 || vehicleArray.vehicles[i]->classCode == 5 ||
            vehicleArray.vehicles[i]->classCode == 6) {
            totalCount++;
            if (vehicleArray.vehicles[i]->weight > 10000.0)
                heavyCount++;
        }
    }

    return (float) heavyCount * 100 / totalCount;
}

float shortMotorCycleCarRatio(VehicleArray vehicleArray) {
    int totalCount = 0, shortCount = 0;
    for (size_t i = 0; i < vehicleArray.size; i++) {
        if (vehicleArray.vehicles[i]->classCode == 1 || vehicleArray.vehicles[i]->classCode == 2) {
            totalCount++;
            if (vehicleArray.vehicles[i]->minuteInParking <= 30)
                shortCount++;
        }
    }

    return (float) shortCount * 100 / totalCount;
}

float longMinibusBusRatio(VehicleArray vehicleArray) {
    int totalCount = 0, longCount = 0;
    for (size_t i = 0; i < vehicleArray.size; i++) {
        if (vehicleArray.vehicles[i]->classCode == 3 || vehicleArray.vehicles[i]->classCode == 4) {
            totalCount++;
            if (vehicleArray.vehicles[i]->minuteInParking > 1440)
                longCount++;
        }
    }

    return (float) longCount * 100 / totalCount;
}

float longWorthyVehicles(VehicleArray vehicleArray) {
    int longWorthyCount = 0;
    for (size_t i = 0; i < vehicleArray.size; i++) {
        if (vehicleArray.vehicles[i]->minuteInParking > 43200 || vehicleArray.vehicles[i]->parkingFee > 900)
            longWorthyCount++;
    }

    return (float) longWorthyCount * 100 / vehicleArray.size;
}

int specStateVehicleCount(VehicleArray vehicleArray, int specCode) {
    bool statement;
    int specVehicleCount = 0;
    for (size_t i = 0; i < vehicleArray.size; i++) {
        statement = (specCode == 1) ? strcmp(vehicleArray.vehicles[i]->specificStateOfDriver, "Veteran") == 0
                                    : strcmp(vehicleArray.vehicles[i]->specificStateOfDriver, "Disabled") == 0;
        if (statement)
            specVehicleCount++;
    }

    return specVehicleCount;
}

int averageMinuteForSpecVehicles(VehicleArray vehicleArray, int specCode) {
    bool statement;
    int specVehicleMinute = 0;
    for (size_t i = 0; i < vehicleArray.size; i++) {
        statement = (specCode == 1) ? strcmp(vehicleArray.vehicles[i]->specificStateOfDriver, "Veteran") == 0
                                    : strcmp(vehicleArray.vehicles[i]->specificStateOfDriver, "Disabled") == 0;
        if (statement)
            specVehicleMinute += vehicleArray.vehicles[i]->minuteInParking;
    }

    return specVehicleMinute / specStateVehicleCount(vehicleArray, specCode);
}

float longDiscountedVehicleCount(VehicleArray vehicleArray) {
    int longDiscountedCount = 0;
    for (size_t i = 0; i < vehicleArray.size; i++) {
        if (vehicleArray.vehicles[i]->minuteInParking > 180 && vehicleArray.vehicles[i]->discountRate != 0)
            longDiscountedCount++;
    }

    return (float) longDiscountedCount * 100 /
           (specStateVehicleCount(vehicleArray, 1) + specStateVehicleCount(vehicleArray, 2));
}

Vehicle *longestVehicle(VehicleArray vehicleArray) {
    int longestMinute = 0;
    size_t longestVehicleIndex = 0;
    for (size_t i = 0; i < vehicleArray.size; i++) {
        if (vehicleArray.vehicles[i]->minuteInParking > longestMinute) {
            longestMinute = vehicleArray.vehicles[i]->minuteInParking;
            longestVehicleIndex = i;
        }
    }

    return vehicleArray.vehicles[longestVehicleIndex];
}

Vehicle *worthiestCar(VehicleArray vehicleArray) {
    float mostParkingFee = 0.0f;
    size_t longestCarIndex = 0;
    for (size_t i = 0; i < vehicleArray.size; i++) {
        if (vehicleArray.vehicles[i]->classCode == 2 && vehicleArray.vehicles[i]->parkingFee > mostParkingFee) {
            mostParkingFee = vehicleArray.vehicles[i]->parkingFee;
            longestCarIndex = i;
        }
    }

    return vehicleArray.vehicles[longestCarIndex];
}
