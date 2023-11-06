#include "functions.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "dataCaller.h"
//Runs the application
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
        printTankStatus(tank);
    } else if (strcmp(input, "simulation") == 0) {
        runSimulation();
    } else if (strcmp(input, "hydrogen") == 0){
        printHydrogen();
    }

}

void runSimulation() {
    date startingDate;
    printf("Choose a starting date and time: (yyyy-mm-dd-HH)\n");
    scanf("%d-%d-%d-%d",
          &startingDate.year, &startingDate.month,
          &startingDate.day, &startingDate.hour
    );

    while(1) {
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
    }else if (strcmp(input, "graph") == 0) {
        return 1;
    } else if (strcmp(input, "table") == 0) {
        return 1;
    } else if (strcmp(input, "hydrogen") == 0) {
        return 1;
    } else if (strcmp(input, "prognosis") == 0) {
        return 1;
    } else if (strcmp(input, "simulation") == 0) {
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

void printTankStatus(hydrogenTank tank) {
    double hydrogen_status = tankPercentageFull(tank);
    double electricitySpent = (tank.totalElectricityUsedKwH);
    double hydrogenAmount = (tank.hydrogenAmountKg);
    double hydrogenProduced = (tank.totalAmountOfHydrogenProducedKg);
    printf("The tank is %.1lf%% full\n", hydrogen_status);
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

//Function that tells us how much hydrogen is produced on a certain date
void printHydrogen (date inputDate){

    double exceedingElectricity; //Skal være for en specifik dag
    double producedHydrogen;

    producedHydrogen = exceedingElectricity /KWH_PER_KG_HYDROGEN;

    printf("Enter a date and time: (yyyy-mm-dd-HH)");
    scanf("%d-%d-%d-%d", &inputDate.year, &inputDate.month, &inputDate.day, &inputDate.hour);

    printf("On the day: %d-%d-%d-%d\n %lf kgs of hydrogen was produced.",
           inputDate.year, inputDate.month, inputDate.day, inputDate.hour, producedHydrogen);

};

double exceedingElectricity(date inputDate, hydrogenTank tank){
    double electricity_exceeding;
    double electricityProduced;
    electricity_exceeding = electricityProduced - tank.totalElectricityUsedKwH;

};
