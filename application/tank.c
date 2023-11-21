#include "tank.h"
#include <stdio.h>
#include "functions.h"
#include <stdlib.h>
#include <math.h>
#include "structs.h"
#include <string.h>

//This function finds out if the tank full
double isTankFull(hydrogenTank *tank) {
    if (tank->hydrogenAmountKg >= tank->maxAmountKg) {
        return 1;
    } else return 0;
}

//This function tells us how much free space there is in the tank
double tankFreeSpace(hydrogenTank *tank) {
    double calSpaceInTank;

    calSpaceInTank = (tank->maxAmountKg - tank->hydrogenAmountKg);

    return calSpaceInTank;
}

//This function checks if the amount of hydrogen that is being added does not exceed the max amount of our tank
int isValidIncreaseOfHydrogen(hydrogenTank *tank, double amountIncrease) {
    if ((amountIncrease + tank->hydrogenAmountKg) > tank->maxAmountKg) {
        return 0;
    } else return 1;
}

double convertElectricityToHydrogen(double electricityMWh) {
    if (electricityMWh >= 0) {
        double result = (electricityMWh / MWH_PER_KG_HYDROGEN) * EL_TO_H_CONV_RATE;
        return result;
    } else {
        return 0;
    }
}

// Shows how full the hydrogen tank is in percentages.
double tankPercentageFull(hydrogenTank *tank) {
    double hydrogen_status = (tank->hydrogenAmountKg / tank->maxAmountKg) * 100;
    return hydrogen_status;
}

void printVirtualTank(hydrogenTank *tank) {
    double hydrogen_status = tankPercentageFull(tank);
    double electricitySpent = (tank->totalElectricityUsedMwH);
    double hydrogenAmount = (tank->hydrogenAmountKg);
    double hydrogenProduced = (tank->totalAmountOfHydrogenProducedKg);


    printf("|--------------------|\n|");
    int counter = 200 - floor(hydrogen_status * 2);
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

void printTankStatus(hydrogenTank *tank) {
    printf("The tank is %.2lf%% full\n", tankPercentageFull(tank));
    printf("Total amount of hydrogen in the tank: %.lf kg\n", tank->hydrogenAmountKg);
    printf("Total amount of hydrogen produced: %.lf kg\n", tank->totalAmountOfHydrogenProducedKg);
    printf("Total amount of excess electricity used: %.lf MWh\n", tank->totalElectricityUsedMwH);
    printf("Total amount of space in the tank: %.lf kg\n", tank->maxAmountKg);
    printf("Total amount of electricity made by hydrogen: %.lf MWh\n", tank->electricityMadeByHydrogenMwH);
};

//Function to increase our hydrogen amount in our tank
void increaseTank(hydrogenTank *tank, double kg) {
    if (isValidIncreaseOfHydrogen(tank, kg)) {
        tank->hydrogenAmountKg += kg;
    } else {
        double freeSpaceInTank = tankFreeSpace(tank);
        double increaseWith = freeSpaceInTank;
        tank->hydrogenAmountKg += increaseWith;
    }
}

//Function to decrease our hydrogen amount in our tank
void decreaseTank(hydrogenTank *tank, double kg) {
    tank->hydrogenAmountKg -= kg;
}

void increaseTotalAmountOfExcessElectricity(hydrogenTank *tank, double MwH) {
    if (MwH >= 0) {
        tank->totalElectricityUsedMwH += MwH;
    }
}

void increaseTotalAmountOfHydrogenProduced(hydrogenTank *tank, double kg) {
    if (isValidIncreaseOfHydrogen(tank, kg)) {
        tank->totalAmountOfHydrogenProducedKg += kg;
    } else {
        double freeSpaceInTank = tankFreeSpace(tank);
        double increaseWith = freeSpaceInTank;
        tank->totalAmountOfHydrogenProducedKg += increaseWith;
    }
}

double calculateExcessEnergy(hydrogenTank* tank,date currentDate){

    double production = getGrossProduction(currentDate);
    double consumption = getGrossConsumption(currentDate);
    double gridLoss = getGrossGridLoss(currentDate);
    double excessEnergy = production - consumption - gridLoss;

    return excessEnergy;
}

double convertHydrogenToElectricity(double hydrogenKG) {
    if (hydrogenKG <= 0) {
        return 0;
    } else {
        double resultMwH;
        resultMwH = (hydrogenKG * MWH_PER_KG_HYDROGEN) * H_TO_EL_CONV_RATE;
        return resultMwH;
    }
}
