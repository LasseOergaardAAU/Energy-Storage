#include "functions.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "dataCaller.h"
#include "time.h"
#include "unistd.h"
#include "structs.h"
#include "tank.h"
#include "dates.h"
#include "time.h"
#include <conio.h>

void runApplication() {
    hydrogenTank tank = {0, 0, 0, 8320000};
    char *commands[] = {"quit", "help", "simulation", "data", "status", "reset", "convert"};
    int commandsLength = sizeof(commands) / sizeof(commands[0]);

    while (1) {
        printf("Write a command.\n>");
        char input[30];
        scanf("%s", input);
        strlwr(input);
        if (!isValidInput(input, commands, commandsLength)) {
            printf("Invalid input. Try again\n");
            continue;
        }
        doNextOperation(input, &tank, commands, commandsLength);
    }
}

// Decides what the operation will do.
void doNextOperation(char input[], hydrogenTank *tank, char *commands[], int commandsLength) {
    if (strcmp(input, "quit") == 0) {
        exit(0);
    } else if (strcmp(input, "help") == 0) {
        printCommands(commands, commandsLength);
    } else if (strcmp(input, "status") == 0) {
        printVirtualTank(tank);
        printTankStatus(tank);
    } else if (strcmp(input, "simulation") == 0) {
        if (isTankFull(tank)) {
            printf("Tank is already full\n");
        } else {
            runSimulation(tank);
        }
    } else if (strcmp(input, "data") == 0) {
        printf("Enter date (yyyy-mm-dd):\n>");
        date inputDate = scanDate();
        printData(inputDate);
    } else if (strcmp(input, "reset") == 0){
        resetTank(tank);
        printf("The tank has been reset.\n");
    } else if (strcmp(input, "convert") == 0){
        // lav funktion som converter alt hydrogen i tank til el.
    }
}

void runSimulation(hydrogenTank *tank) {
    printf("----------------------\n");
    printf("Date has to be between: ");
    date firstDate = getFirstDate();
    printDate(firstDate);
    printf(" & ");
    date lastDate = getLastDate();
    printDate(lastDate);
    printf("\nEnter start date of simulation (yyyy-mm-dd-HH)\n>");
    date startDate = scanDate();
    printf("Enter end date of simulation (yyyy-mm-dd-HH)\n>");
    date endDate = scanDate();

    int simulationLength = (dateToLine(startDate) - dateToLine(endDate)) / 2;
    int startLine = dateToLine(startDate);
    printf("Stop simulation by pressing 'enter'\n");
    sleep(1);

    for (int i = 0; i < simulationLength; ++i) {
        if (_kbhit()) {
            // If a key is pressed, break out of the loop
            break;
        }
        int currentDateLine = startLine - i * 2;
        date currentDate = lineToDate(currentDateLine);
        double excessEnergy = calculateExcessEnergy(currentDate);
        double hydrogen = convertElectricityToHydrogen(excessEnergy);

        if (excessEnergy >= 0) {
            if (!isTankFull(tank) && !isValidIncreaseOfHydrogen(tank, hydrogen)) {
                double freeSpace = tankFreeSpace(tank);
                excessEnergy = freeSpace * MWH_PER_KG_HYDROGEN / EL_TO_H_CONV_RATE;
            }

            increaseTotalAmountOfExcessElectricity(tank, excessEnergy);
            increaseTotalAmountOfHydrogenProduced(tank, hydrogen);
            increaseTank(tank, hydrogen);
        } else {
            if (tankPercentageFull(tank) >= MINIMUM_TANK_PERCENTAGE_FULL) {
                /*random number used to simulate percentage amount
                of underproduction should be covered by hydrogen.*/
                int randomNum = ((rand() % 31) + 15);
                double availableHydrogen =
                        ((tankPercentageFull(tank) - MINIMUM_TANK_PERCENTAGE_FULL) / 100) * tank->maxAmountKg;
                double energyShareEl = (-1 * (excessEnergy) * (double) randomNum) / 100;
                double energyShareHydrogen = (energyShareEl / EL_TO_H_CONV_RATE) / MWH_PER_KG_HYDROGEN;

                if (availableHydrogen < energyShareHydrogen) {
                    energyShareHydrogen = availableHydrogen;
                    energyShareEl = availableHydrogen * MWH_PER_KG_HYDROGEN / EL_TO_H_CONV_RATE;
                }

                decreaseTank(tank, energyShareHydrogen);
                tank->electricityMadeByHydrogenMwH += energyShareEl;

            }
        }

        printf("\n");
        printVirtualTank(tank);
        printf("Hydrogen in the tank: %.lf kg\n", tank->hydrogenAmountKg);

        if (isTankFull(tank)) {
            break;
        }
        //sleep(1);

    }
    printf("-------------------------------------\n");

    if (isTankFull(tank)) {
        printf("Simulation stopped, tank is full.\n");
    } else {
        printf("Simulation is over.\n");
    }
    printf("-------------------------------------\n");

    printTankStatus(tank);
}


int isValidInput(char input[], char *commands[], int arrLength) {
    for (int i = 0; i < arrLength; ++i) {
        if (strcmp(input, commands[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

void printCommands(char *commands[], int arrLength) {

    printf("]----------------------------------------------------[\n");
    for (int i = 0; i < arrLength; ++i) {
        int shouldBeLength = 14;
        int strLength = strlen(commands[i]);
        printf("|");
        for (int j = 0; j < (shouldBeLength - strLength) / 2; ++j) {
            printf(" ");
        }
        printf("'%s'", commands[i]);
        for (int j = 0; j < (shouldBeLength - strLength) / 2; ++j) {
            printf(" ");
        }
        if (strLength % 2 == 1) {
            printf(" ");
        }
        printf("|");
        if ((i + 1) % 3 == 0 && i != arrLength - 1) {
            printf("\n");
            printf("|----------------------------------------------------|\n");

        }
    }
    printf("\n");
    printf("]----------------------------------------------------[\n");
}

//prints data for a whole day in a table.
void printData(date inputDate) {
    char buffer[1000];
    inputDate.hour = 23;
    int startLine = dateToLine(inputDate);

    int productionShouldBeLength = 15;
    int consumptionShouldBeLength = 15;
    int gridlossShouldBeLength = 14;
    int excessElectricityShouldBeLength = 15;
    int hydrogenShouldBeLength = 14;
    double totalProduction = 0;
    double totalConsumption = 0;
    double totalGridLoss = 0;
    double totalExcessEnergy = 0;
    double totalHydrogen = 0;
    char tempStr[20];


    FILE *filePointer = fopen("EPAU.csv", "r");

    if (filePointer == NULL) {
        exit(-1);
    }


    for (int i = 0; i < startLine + 1; ++i) {
        fgets(buffer, sizeof(buffer), filePointer);
    }
    printf("                             [ Data Table for %d-%d-%d ] \n", inputDate.year, inputDate.month, inputDate.day);
    printf("+-------+---------------+---------------+--------------+---------------+--------------+\n");
    printf("| Time  | Production    | Consumption   | Gridloss     | Excess Energy | Hydrogen     |\n");
    printf("+-------+---------------+---------------+--------------+---------------+--------------+\n");

    for (int i = 0; i < 24; ++i) {
        char *tempBuffer = strdup(buffer);
        char *dateStr = strtok(tempBuffer, ";");
        date currentDate = stringToDate(dateStr);

        //Prints hour:
        printf("| %s |", dataStringToHour(buffer));

        //Prints productions
        double grossProduction = getGrossProduction(currentDate);
        totalProduction += grossProduction;
        printf(" %.2lf MWh ", grossProduction);
        sprintf(tempStr, " %.2lf MWh ", grossProduction);
        for (int j = 0; j < productionShouldBeLength - strlen(tempStr); ++j) {
            printf(" ");
        }
        printf("|");

        //Prints consumption
        double grossConsumption = getGrossConsumption(currentDate);
        totalConsumption += grossConsumption;
        printf(" %.2lf MWh ", grossConsumption);
        sprintf(tempStr, " %.2lf MWh ", grossConsumption);
        for (int j = 0; j < consumptionShouldBeLength - strlen(tempStr); ++j) {
            printf(" ");
        }
        printf("|");

        // Prints the grid loss
        double grossGridLoss = getGrossGridLoss(currentDate);
        totalGridLoss += grossGridLoss;
        printf(" %.2lf MWh ", grossGridLoss);
        sprintf(tempStr, " %.2lf MWh ", grossGridLoss);
        for (int j = 0; j < gridlossShouldBeLength - strlen(tempStr); ++j) {
            printf(" ");
        }
        printf("|");

        // Prints the excess energy, and prints 0 if the result is below 0
        double grossExcessEnergy = calculateExcessEnergy(currentDate);

        if(calculateExcessEnergy(currentDate) < 0) {
            printf(" 0.00 MWh ");
            sprintf(tempStr, " 0.00 MWh ");
        } else {
            totalExcessEnergy += grossExcessEnergy;
            printf(" %.2lf MWh ", grossExcessEnergy);
            sprintf(tempStr, " %.2lf MWh ", grossExcessEnergy);
        }
        for (int j = 0; j < excessElectricityShouldBeLength - strlen(tempStr); ++j) {
            printf(" ");
        }
        printf("|");

        //Prints hydrogen made by the excess energy
        double hydrogenKg = convertElectricityToHydrogen(calculateExcessEnergy(currentDate));
        totalHydrogen += hydrogenKg;
        printf(" %.2lf kg ", hydrogenKg);
        sprintf(tempStr, " %.2lf kg ", hydrogenKg);
        for (int j = 0; j < hydrogenShouldBeLength - strlen(tempStr); ++j) {
            printf(" ");
        }
        printf("|");

        printf("\n");
        fgets(buffer, sizeof(buffer), filePointer);
        fgets(buffer, sizeof(buffer), filePointer);
    }
    printf("+-------+---------------+---------------+--------------+---------------+--------------+\n");
    printf("| Total |");
    printf(" %.2lf MWh ", totalProduction);
    sprintf(tempStr, " %.2lf MWh ", totalProduction);
    for (int j = 0; j < productionShouldBeLength - strlen(tempStr); ++j) {
        printf(" ");
    }
    printf("|");
    printf(" %.2lf MWh ", totalConsumption);
    sprintf(tempStr, " %.2lf MWh ", totalConsumption);
    for (int j = 0; j < consumptionShouldBeLength - strlen(tempStr); ++j) {
        printf(" ");
    }
    printf("|");
    printf(" %.2lf MWh ", totalGridLoss);
    sprintf(tempStr, " %.2lf MWh ", totalGridLoss);
    for (int j = 0; j < gridlossShouldBeLength - strlen(tempStr); ++j) {
        printf(" ");
    }
    printf("|");
    printf(" %.2lf MWh ", totalExcessEnergy);
    sprintf(tempStr, " %.2lf MWh ", totalExcessEnergy);
    for (int j = 0; j < excessElectricityShouldBeLength - strlen(tempStr); ++j) {
        printf(" ");
    }
    printf("|");
    printf(" %.2lf kg ", totalHydrogen);
    sprintf(tempStr, " %.2lf kg ", totalHydrogen);
    for (int j = 0; j < hydrogenShouldBeLength - strlen(tempStr); ++j) {
        printf(" ");
    }
    printf("|");
    printf("\n");
    printf("+-------+---------------+---------------+--------------+---------------+--------------+\n");

    fclose(filePointer);
}



