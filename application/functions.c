#include "functions.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "dataCaller.h"
#include "time.h"

void runApplication() {
    //Our tank has a capacity of 10 tonnes.
    hydrogenTank tank = {0, 0, 0, 10000};

    while (1) {
        printf("Write a command.\n>");
        char input[30];
        scanf("%s", input);
        strlwr(input);
        if (!isValidInput(input)) {
            printf("Invalid input. Try again\n");
            continue;
        }
        doNextOperation(input, tank);
    }
}

// Decides what the operation will do.
void doNextOperation(char input[], hydrogenTank tank) {
    if (strcmp(input, "quit") == 0) {
        printf("Quitting the application.");
        exit(0);
    } else if (strcmp(input, "help") == 0) {
        printf("Here you have the different commands that you can input: \n>status\n>quit\n>graph\n>table\n>prognosis\n>hydrogen\n");
    } else if (strcmp(input, "status") == 0) {
        printTank(tank);
    } else if (strcmp(input, "simulation") == 0) {
        runSimulation();
    } else if (strcmp(input, "hydrogen") == 0) {
        //printHydrogen();
    } else if (strcmp(input, "data") == 0) {
        date dataDate = scanDate();
        getGrossConsumption(dataDate);
    }
}

void runSimulation() {
    date startingDate;
    printf("Choose a starting date and time: (yyyy-mm-dd-HH)\n");
    scanf("%d-%d-%d-%d",
          &startingDate.year, &startingDate.month,
          &startingDate.day, &startingDate.hour
    );
    while (1) {
        printDate(startingDate);
    }
}

void printDate(date inputDate) {
    printf("%d-%d-%d-%d\n",
           inputDate.year, inputDate.month,
           inputDate.day, inputDate.hour
    );
}

int isValidInput(char input[]) {
    if (strcmp(input, "quit") == 0) {
        return 1;
    } else if (strcmp(input, "help") == 0) {
        return 1;
    } else if (strcmp(input, "status") == 0) {
        return 1;
    } else if (strcmp(input, "graph") == 0) {
        return 1;
    } else if (strcmp(input, "table") == 0) {
        return 1;
    } else if (strcmp(input, "hydrogen") == 0) {
        return 1;
    } else if (strcmp(input, "prognosis") == 0) {
        return 1;
    } else if (strcmp(input, "simulation") == 0) {
        return 1;
    } else if (strcmp(input, "data") == 0) {
        return 1;
    } else {
        return 0;
    }
}

// Shows how full the hydrogen tank is in percentages.
double tankPercentageFull(hydrogenTank tank) {
    double hydrogen_status = (tank.hydrogenAmountKg / tank.maxAmountKg) * 100;
    return hydrogen_status;
}

void printTank(hydrogenTank tank) {
    double hydrogen_status = tankPercentageFull(tank);
    double electricitySpent = (tank.totalElectricityUsedKwH);
    double hydrogenAmount = (tank.hydrogenAmountKg);
    double hydrogenProduced = (tank.totalAmountOfHydrogenProducedKg);

    //printer den virtuelle tank
    printf("|----------|\n|");
    int counter = 100 - hydrogen_status;
    for (int i = 0; i < 100; ++i) {
        if (i % 10 == 0 & i >= 10) {
            printf("|\n|");
        }
        if (counter <= 0) {
            printf("#");
        } else {
            printf(" ");
        }
        counter--;
    }
    printf("|\n");
    printf("|----------|\n");
    printf("The tank is %.d%% full\n", hydrogen_status);

    printf("The amount of hydrogen in the tank is %.1lf kg\n", hydrogenAmount);
    printf("The amount of electricity spent on producing that hydrogen: %.1lf\n", electricitySpent);
    printf("The amount of hydrogen produced %.1lf kg\n", hydrogenProduced);
};

//Function to increase our hydrogen amount in our tank
hydrogenTank increaseTank(hydrogenTank tank, double kg) {
    tank.hydrogenAmountKg += kg;
    return tank;
}

//Function to decrease our hydrogen amount in our tank
hydrogenTank decreaseTank(hydrogenTank tank, double kg) {
    tank.hydrogenAmountKg -= kg;
    return tank;
}

date scanDate() {
    //Scans for date, and returns date as a struct 'date'.
    char dateStr[13];
    date dateStruct;
    printf("Insert date (yyyy-mm-dd-HH)\n>");
    scanf("%s", dateStr);

    char *token = strtok(dateStr, "-");
    dateStruct.year = atoi(token);

    token = strtok(NULL, "-");
    dateStruct.month = atoi(token);

    token = strtok(NULL, "-");
    dateStruct.day = atoi(token);

    token = strtok(NULL, "-");
    dateStruct.hour = atoi(token);

    return dateStruct;
}




