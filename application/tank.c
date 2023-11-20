#include "tank.h"
#include <stdio.h>
#include "functions.h"
#include <stdlib.h>
#include <math.h>
#include "structs.h"
#include <string.h>

//This funktion finds out if the tank full
double isTankFull(hydrogenTank tank) {
    if (tank.hydrogenAmountKg == tank.maxAmountKg) {
        return 1;
    } else return 0;
}

//This function tells us how much free space there is in the tank
double tankFreeSpace(hydrogenTank tank) {
    double calSpaceInTank;

    calSpaceInTank = (tank.maxAmountKg - tank.hydrogenAmountKg);

    return calSpaceInTank;
}

//This function checks if the amount of hydrogen that is being added does not exceed the max amount of our tank
int isValidIncreaseOfHydrogen(hydrogenTank tank, double amountIncrease) {
    if ((amountIncrease + tank.hydrogenAmountKg) > tank.maxAmountKg) {
        return 0;
    } else return 1;
}

double convertElectricityToHydrogen(double electricityMWh) {
    if ( electricityMWh >= 0) {
        double result = (electricityMWh / MWH_PER_KG_HYDROGEN) * EL_TO_H_CONV_RATE;
        return result;
    } else {
        return 0;
    }
}

// Shows how full the hydrogen tank is in percentages.
double tankPercentageFull(hydrogenTank tank) {
    double hydrogen_status = (tank.hydrogenAmountKg / tank.maxAmountKg) * 100;
    return hydrogen_status;
}

void printVirtualTank(hydrogenTank tank) {
    double hydrogen_status = tankPercentageFull(tank);
    double electricitySpent = (tank.totalElectricityUsedKwH);
    double hydrogenAmount = (tank.hydrogenAmountKg);
    double hydrogenProduced = (tank.totalAmountOfHydrogenProducedKg);

    //printer den virtuelle tank
    printf("|--------------------|\n|");
    int counter = 200 - floor(hydrogen_status*2);
    for (int i = 0; i < 200; ++i) {
        if (i % 20 == 0 & i >= 10) {
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
    printf("|--------------------|\n");
};

void printTankStatus(hydrogenTank tank) {

    printf("The tank is %.2lf%% full\n", tankPercentageFull(tank));
    printf("Total amount of hydrogen in the tank: %.lf kg\n", tank.hydrogenAmountKg);
    printf("Total amount of hydrogen produced: %.lf kg\n", tank.totalAmountOfHydrogenProducedKg);
    printf("Total amount of excess electricity used: %.lf MWh\n", tank.totalElectricityUsedKwH);
    printf("Total amount of space in the tank: %.lf kg\n", tank.maxAmountKg);

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

hydrogenTank increaseTotalAmountOfExcessElectricity (hydrogenTank tank, double KwH){
    tank.totalElectricityUsedKwH += KwH;
    return tank;
}