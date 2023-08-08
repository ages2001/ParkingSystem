#include "parking.h"

int main() {
    VehicleArray *vehicleList = (VehicleArray *) malloc(sizeof(VehicleArray));
    if (vehicleList == NULL) {
        fprintf(stderr, "Memory allocation failed!\n");
        return 1;
    }

    vehicleList->vehicles = (Vehicle **) malloc(sizeof(Vehicle *) * (PARK_LIMIT + 1));
    if (vehicleList->vehicles == NULL) {
        fprintf(stderr, "Memory allocation failed!\n");
        clearVehicleArray(vehicleList);
        return 1;
    }

    vehicleList->size = 0;
    char addVehicle = 'Y';

    do {
        Vehicle *newVehicle = (Vehicle *) malloc(sizeof(Vehicle));
        newVehicle->plate = (char *) malloc(sizeof(char) * STR_LIMIT);
        newVehicle->driverNameSurname = (char *) malloc(sizeof(char) * STR_LIMIT);
        newVehicle->specificStateOfDriver = (char *) malloc(sizeof(char) * STR_LIMIT);

        if (newVehicle == NULL || newVehicle->plate == NULL || newVehicle->driverNameSurname == NULL ||
            newVehicle->specificStateOfDriver == NULL) {
            fprintf(stderr, "Memory allocation failed!\n");
            free(newVehicle->plate);
            free(newVehicle->driverNameSurname);
            free(newVehicle->specificStateOfDriver);
            free(newVehicle);

            clearVehicleArray(vehicleList);
            return 1;
        }

        printf("\nEnter the vehicle's license plate: ");
        scanf("%s", newVehicle->plate);

        do {
            printf("Enter the vehicle's class code (1-6): ");
            scanf("%d", &newVehicle->classCode);

            if (newVehicle->classCode < 1 ||
                newVehicle->classCode > 6)
                printf("Invalid class code!\n");
        } while (newVehicle->classCode < 1 ||
                 newVehicle->classCode > 6);

        do {
            printf("Enter the vehicle's weight (kg): ");
            scanf("%f", &newVehicle->weight);

            if (newVehicle->weight <= 0)
                printf("Invalid weight!\n");
        } while (newVehicle->weight <= 0);

        do {
            printf("Enter the vehicle's minute in the parking lot: ");
            scanf("%d", &newVehicle->minuteInParking);

            if (newVehicle->minuteInParking <= 0)
                printf("Invalid minute!\n");
        } while (newVehicle->minuteInParking <= 0);

        printf("Enter the vehicle's driver's name-surname: ");
        scanf("%s", newVehicle->driverNameSurname);

        char specState;
        if (newVehicle->classCode == 1 || newVehicle->classCode == 2) {
            do {
                printf("Enter the vehicle's driver's specific state (N/V/D): ");
                scanf(" %c", &specState);

                if (!(toupper(specState) == 'N' || toupper(specState) == 'V' || toupper(specState) == 'D'))
                    printf("Invalid specific state entered!\n");
            } while (!(toupper(specState) == 'N' || toupper(specState) == 'V' || toupper(specState) == 'D'));

            if (toupper(specState) == 'N') strcpy(newVehicle->specificStateOfDriver, "No");
            else if (toupper(specState) == 'V')
                strcpy(newVehicle->specificStateOfDriver, "Veteran");
            else strcpy(newVehicle->specificStateOfDriver, "Disabled");
        }

        calculateParkingFee(newVehicle);

        vehicleList->vehicles[vehicleList->size] = newVehicle;

        printf("\n Vehicle %zu:\n************\n", vehicleList->size + 1);
        printVehicleInfo(*vehicleList->vehicles[vehicleList->size++]);

        if (vehicleList->size < PARK_LIMIT) {
            do {
                printf("\n\nDo you want to add more vehicle? (Y/N): ");
                scanf("%s", &addVehicle);

                if (!(toupper(addVehicle) == 'Y' || toupper(addVehicle) == 'N'))
                    printf("Invalid choice entered!\n");
            } while (!(toupper(addVehicle) == 'Y' || toupper(addVehicle) == 'N'));
        }
    } while (toupper(addVehicle) == 'Y' && vehicleList->size < PARK_LIMIT);

    if (vehicleList->size == PARK_LIMIT)
        printf("\n\nThe parking lot is full!\n");

    printf("\nTotal number of vehicles: %zu\n\n", vehicleList->size);
    printf("Vehicle Class    Count     Ratio\n");
    printf("-------------    -----    -------\n");
    printf(" Motorcycle        %d      %.2f %%\n", countOfClassName(*vehicleList, 1),
           (float) countOfClassName(*vehicleList, 1) * 100 / vehicleList->size);
    printf("    Car            %d      %.2f %%\n", countOfClassName(*vehicleList, 2),
           (float) countOfClassName(*vehicleList, 2) * 100 / vehicleList->size);
    printf("  Minibus          %d      %.2f %%\n", countOfClassName(*vehicleList, 3),
           (float) countOfClassName(*vehicleList, 3) * 100 / vehicleList->size);
    printf("    Bus            %d      %.2f %%\n", countOfClassName(*vehicleList, 4),
           (float) countOfClassName(*vehicleList, 4) * 100 / vehicleList->size);
    printf("   Truck           %d      %.2f %%\n", countOfClassName(*vehicleList, 5),
           (float) countOfClassName(*vehicleList, 5) * 100 / vehicleList->size);
    printf("   Lorry           %d      %.2f %%\n", countOfClassName(*vehicleList, 6),
           (float) countOfClassName(*vehicleList, 6) * 100 / vehicleList->size);

    printf("\nTotal revenue: %.2f TL\n\n", totalRevenue(*vehicleList));
    printf("Vehicle Class    Total Revenue    Ratio\n");
    printf("-------------    -------------   -------\n");
    printf(" Motorcycle        %.2f TL       %.2f %%\n", totalRevenueForClassName(*vehicleList, 1),
           totalRevenueForClassName(*vehicleList, 1) * 100 / totalRevenue(*vehicleList));
    printf("    Car            %.2f TL     %.2f %%\n", totalRevenueForClassName(*vehicleList, 2),
           totalRevenueForClassName(*vehicleList, 2) * 100 / totalRevenue(*vehicleList));
    printf("  Minibus          %.2f TL      %.2f %%\n", totalRevenueForClassName(*vehicleList, 3),
           totalRevenueForClassName(*vehicleList, 3) * 100 / totalRevenue(*vehicleList));
    printf("    Bus            %.2f TL      %.2f %%\n", totalRevenueForClassName(*vehicleList, 4),
           totalRevenueForClassName(*vehicleList, 4) * 100 / totalRevenue(*vehicleList));
    printf("   Truck           %.2f TL     %.2f %%\n", totalRevenueForClassName(*vehicleList, 5),
           totalRevenueForClassName(*vehicleList, 5) * 100 / totalRevenue(*vehicleList));
    printf("   Lorry           %.2f TL      %.2f %%\n", totalRevenueForClassName(*vehicleList, 6),
           totalRevenueForClassName(*vehicleList, 6) * 100 / totalRevenue(*vehicleList));

    printf("\nVehicle Class        Average Time         Total Revenue\n");
    printf("-------------    ---------------------    -------------\n");
    printf(" Motorcycle       %d Day %d Hour %d Min        %.2f TL\n",
           averageMinuteForClassName(*vehicleList, 1) / (24 * 60),
           averageMinuteForClassName(*vehicleList, 1) % (24 * 60) / 60,
           averageMinuteForClassName(*vehicleList, 1) % 60,
           totalRevenueForClassName(*vehicleList, 1) / countOfClassName(*vehicleList, 1));
    printf("    Car           %d Day %d Hour %d Min       %.2f TL\n",
           averageMinuteForClassName(*vehicleList, 2) / (24 * 60),
           averageMinuteForClassName(*vehicleList, 2) % (24 * 60) / 60,
           averageMinuteForClassName(*vehicleList, 2) % 60,
           totalRevenueForClassName(*vehicleList, 2) / countOfClassName(*vehicleList, 2));
    printf("  Minibus         %d Day %d Hour %d Min        %.2f TL\n",
           averageMinuteForClassName(*vehicleList, 3) / (24 * 60),
           averageMinuteForClassName(*vehicleList, 3) % (24 * 60) / 60,
           averageMinuteForClassName(*vehicleList, 3) % 60,
           totalRevenueForClassName(*vehicleList, 3) / countOfClassName(*vehicleList, 3));
    printf("    Bus           %d Day %d Hour %d Min        %.2f TL\n",
           averageMinuteForClassName(*vehicleList, 4) / (24 * 60),
           averageMinuteForClassName(*vehicleList, 4) % (24 * 60) / 60,
           averageMinuteForClassName(*vehicleList, 4) % 60,
           totalRevenueForClassName(*vehicleList, 4) / countOfClassName(*vehicleList, 4));
    printf("   Truck          %d Day %d Hour %d Min      %.2f TL\n",
           averageMinuteForClassName(*vehicleList, 5) / (24 * 60),
           averageMinuteForClassName(*vehicleList, 5) % (24 * 60) / 60,
           averageMinuteForClassName(*vehicleList, 5) % 60,
           totalRevenueForClassName(*vehicleList, 5) / countOfClassName(*vehicleList, 5));
    printf("   Lorry          %d Day %d Hour %d Min      %.2f TL\n",
           averageMinuteForClassName(*vehicleList, 6) / (24 * 60),
           averageMinuteForClassName(*vehicleList, 6) % (24 * 60) / 60,
           averageMinuteForClassName(*vehicleList, 6) % 60,
           totalRevenueForClassName(*vehicleList, 6) / countOfClassName(*vehicleList, 6));

    printf("\nRatio of cars weighing less than 1 ton among all cars: %.2f %%\n",
           (float) lightCarCount(*vehicleList) * 100 / countOfClassName(*vehicleList, 2));

    printf("\nRatio of bus, truck and lorry class vehicles with a weight of more than 10 tons in all bus, truck and lorry class vehicles: %.2f %%\n",
           heavyBusTruckLorryRatio(*vehicleList));

    printf("\nRatio of motorcycle and car vehicles that stay in the parking lot for 30 minutes or less in all motorcycle and car vehicles: %.2f %%\n",
           shortMotorCycleCarRatio(*vehicleList));

    printf("\nThe ratio of minibus and bus type vehicles staying in the parking lot for more than 1 day among all minibus and bus type vehicles: %.2f %%\n",
           longMinibusBusRatio(*vehicleList));

    printf("\nThe ratio of vehicles staying in the parking lot for more than 30 days or with an income higher than 900 TL among all vehicles: %.2f %%\n",
           longWorthyVehicles(*vehicleList));

    printf("\nSpecific State    Count of Vehicles    Rate in All        Average Time\n");
    printf("--------------    -----------------    -----------    ----------------------\n");
    printf("   Veteran               %d               %.2f %%       %d Day %d Hour %d Min\n",
           specStateVehicleCount(*vehicleList, 1),
           (float) specStateVehicleCount(*vehicleList, 1) * 100 / vehicleList->size,
           averageMinuteForSpecVehicles(*vehicleList, 1) / (24 * 60),
           averageMinuteForSpecVehicles(*vehicleList, 1) % (24 * 60) / 60,
           averageMinuteForSpecVehicles(*vehicleList, 1) % 60);
    printf("   Disabled              %d               %.2f %%       %d Day %d Hour %d Min\n",
           specStateVehicleCount(*vehicleList, 2),
           (float) specStateVehicleCount(*vehicleList, 2) * 100 / vehicleList->size,
           averageMinuteForSpecVehicles(*vehicleList, 2) / (24 * 60),
           averageMinuteForSpecVehicles(*vehicleList, 2) % (24 * 60) / 60,
           averageMinuteForSpecVehicles(*vehicleList, 2) % 60);

    printf("\nThe ratio of discounted vehicles staying in the parking lot for more than 3 hours among all discounted vehicles: %.2f %%\n",
           longDiscountedVehicleCount(*vehicleList));

    printf("\nThe longest time the vehicle stays in the parking lot is %d Day %d Hour %d Minute and the income is %.2f TL.\n",
           longestVehicle(*vehicleList)->minuteInParking / (24 * 60),
           longestVehicle(*vehicleList)->minuteInParking % (24 * 60) / 60,
           longestVehicle(*vehicleList)->minuteInParking % 60,
           longestVehicle(*vehicleList)->parkingFee);

    printf("\nThe time the passenger car with the highest income is left in the parking lot is %d Day %d Hour %d Minute and the income is %.2f TL.\n",
           worthiestCar(*vehicleList)->minuteInParking / (24 * 60),
           worthiestCar(*vehicleList)->minuteInParking % (24 * 60) / 60,
           worthiestCar(*vehicleList)->minuteInParking % 60,
           worthiestCar(*vehicleList)->parkingFee);

    clearVehicleArray(vehicleList);
    return 0;
}
