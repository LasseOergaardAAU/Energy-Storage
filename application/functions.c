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
    hydrogenTank tank = {0, 0, 0, 4532000};
    char *commands[] = {"quit", "help", "simulation", "data", "hydrogen", "prognosis", "table", "graph", "status"};
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
        doNextOperation(input, tank, commands, commandsLength);
    }
}

// Decides what the operation will do.
void doNextOperation(char input[], hydrogenTank tank, char *commands[], int commandsLength) {
    if (strcmp(input, "quit") == 0) {
        exit(0);
    } else if (strcmp(input, "help") == 0) {
        printCommands(commands, commandsLength);
    } else if (strcmp(input, "status") == 0) {
        printVirtualTank(tank);
        printTankStatus(tank);
    } else if (strcmp(input, "simulation") == 0) {
        printf("Enter start date of simulation (yyyy-mm-dd-HH)\n");
        date startDate = scanDate();
        printf("Enter end date of simulation (yyyy-mm-dd-HH)\n");
        date endDate = scanDate();
        runSimulation(startDate, endDate, tank);
    }
}

hydrogenTank runSimulation(date startDate, date endDate, hydrogenTank tank) {
    int simulationLength = (dateToLine(startDate) - dateToLine(endDate)) / 2;
    double result = 0;
    int startLine = dateToLine(startDate);

    for (int i = 0; i < simulationLength; ++i) {
        sleep(1);
        int currectDateLine = startLine - i * 2;
        date currentDate = lineToDate(currectDateLine);

        double production = getGrossProduction(currentDate);
        double consumption = getGrossConsumption(currentDate);
        double excessEnergy = production - consumption;
        double hydrogen = convertElectricityToHydrogen(excessEnergy);
        tank = increaseTank(tank, hydrogen);
        printVirtualTank(tank);
        printTankStatus(tank);
    }
    return tank;
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
    /*if (playerNum == 1) {

        printf("To terminate the program type 'quit' otherwise if you wish to continue."
               " \nHere are the different commands at your disposal: \n\n");

        for (int i = 1; i < arrLength; ++i) {
            printf("['%s'] ", commands[i]);
            if (i%4 == 0){
               printf("\n");
            }


        }
        printf("__________________________________________________");
        printf("\n\n");
    }*/

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

    printf("\n\n");


    /*else if(playerNum == 3) {
        printf("These are the commands you can use in this program\n");
        printf("-----------------------------------------------------------------------------------------------------\n");
        for (int i = 0; i < arrLength; ++i) {
            printf("(%s) - ", commands[i]);
        }
        printf("\n-----------------------------------------------------------------------------------------------------\n");

    }*/
}

