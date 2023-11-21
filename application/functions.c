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


void runApplication() {
    hydrogenTank tank = {0, 0, 0, 45320};
    char *commands[] = {"quit", "help", "simulation", "data", "prognosis", "status"};
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
        date inputDate = scanDate();
        printData(inputDate);
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


    for (int i = 0; i < simulationLength; ++i) {

        int currentDateLine = startLine - i * 2;
        date currentDate = lineToDate(currentDateLine);
        double excessEnergy = calculateExcessEnergy(tank, currentDate);
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

        printVirtualTank(tank);
        printf("The tank is %.2lf%% full\n", tankPercentageFull(tank));
        printf("Total amount of hydrogen in the tank: %.lf kg\n", tank->hydrogenAmountKg);

        if (isTankFull(tank)) {
            break;
        }

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

void printData(date inputDate){
    char buffer[1000];

    FILE* filePointer = fopen("EPAU.csv", "r");

    if (filePointer == NULL) {
        exit(-1);
    }

    inputDate.hour = 23;
    int startLine = dateToLine(inputDate);
    for (int i = 0; i < startLine+1; ++i) {
        fgets(buffer, sizeof(buffer), filePointer);
    }
    printf("+-------+------------+-------------+----------+--------------------+----------+\n");
    printf("| Time  | Production | Consumption | Gridloss | Excess Electricity | Hydrogen |\n");
    printf("+-------+------------+-------------+----------+--------------------+----------+\n");

    for (int i = 0; i < 24; ++i) {
        printf("| %d:00  | 4202 MWh  |  4302 MWh   |  301 MWh  |      103 MWh      | 4501 kg  |\n", 23-i);
        printf("+-------+------------+-------------+----------+--------------------+----------+\n");

    }
    printf("| Total | Production | Consumption | Gridloss | Excess Electricity | Hydrogen |\n");
    printf("+-------+------------+-------------+----------+--------------------+----------+\n");
    fclose(filePointer);
}
