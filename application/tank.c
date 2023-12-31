#include "tank.h"
#include <stdio.h>
#include "functions.h"
#include <stdlib.h>
#include <math.h>
#include "structs.h"
#include <string.h>
#include "dataCaller.h"

// This function return 1 if tank is full
int isTankFull(hydrogenTank *tank) {
    if (tank->hydrogenAmountKg >= tank->maxAmountKg) {
        return 1;
    } else return 0;
}

// This function tells us how much free space there is in the tank
double tankFreeSpace(hydrogenTank *tank) {
    double calSpaceInTank;

    calSpaceInTank = (tank->maxAmountKg - tank->hydrogenAmountKg);

    return calSpaceInTank;
}

// This function checks if the amount of hydrogen that is being added does not exceed the max amount of our tank
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
    char tempStr[10];
    int lidShouldBeLength = 20;
    int leftHyphens = 0;
    int rightHyphens = 0;

    printf("|");
    sprintf(tempStr, "%.1lf%%", tankPercentageFull(tank));
    int percentageLength = strlen(tempStr);
    if (percentageLength % 2 == 1) {
        leftHyphens = ((lidShouldBeLength - percentageLength) / 2) + 1;
        rightHyphens = ((lidShouldBeLength - percentageLength) / 2);
    } else {
        leftHyphens = ((lidShouldBeLength - percentageLength) / 2);
        rightHyphens = ((lidShouldBeLength - percentageLength) / 2);
    }

    for (int i = 0; i < leftHyphens; ++i) {
        printf("-");
    }
    printf("%.1lf%%", tankPercentageFull(tank));

    for (int i = 0; i < rightHyphens; ++i) {
        printf("-");
    }
    printf("|\n|");

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
    printf("Total amount of hydrogen in the tank: %.lf kg\n", tank->hydrogenAmountKg);
    printf("Total amount of hydrogen produced: %.lf kg\n", tank->totalAmountOfHydrogenProducedKg);
    printf("Total amount of excess electricity used: %.lf MWh\n", tank->totalElectricityUsedMwH);
    printf("Total amount of space in the tank: %.lf kg\n", tank->maxAmountKg);
    printf("Total amount of electricity made by hydrogen: %.lf MWh\n", tank->electricityMadeByHydrogenMwH);
    printf("+---------------------------------------------------------------+\n");
}

// Function to increase hydrogen amount in tank
void increaseTank(hydrogenTank *tank, double kg) {
    if (isValidIncreaseOfHydrogen(tank, kg)) {
        tank->hydrogenAmountKg += kg;
    } else {
        double freeSpaceInTank = tankFreeSpace(tank);
        double increaseWith = freeSpaceInTank;
        tank->hydrogenAmountKg += increaseWith;
    }
}

// Function to decrease hydrogen amount in tank
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

double calculateExcessEnergy(date currentDate) {
    double result = getGrossProduction(currentDate) - getGrossConsumption(currentDate) - getGrossGridLoss(currentDate);
    return result;
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

void resetTank(hydrogenTank *tank) {
    tank->hydrogenAmountKg = 0;
    tank->totalAmountOfHydrogenProducedKg = 0;
    tank->totalElectricityUsedMwH = 0;
    tank->electricityMadeByHydrogenMwH = 0;
}

void convertTank(hydrogenTank *tank) {
    double elMWh = convertHydrogenToElectricity(tank->hydrogenAmountKg);
    tank->electricityMadeByHydrogenMwH += elMWh;
    tank->hydrogenAmountKg = 0;
}

void fillTank(hydrogenTank *tank){
    double addHydrogen;
    if (tankPercentageFull(tank) != 100) {
        printf("The tank contains %.lf kg as of right now.\n", tank->hydrogenAmountKg);
        printf("The tank is %.lf kg, how many kgs of hydrogen do you wish to add?\n>", tank->maxAmountKg);
        while(1) {
            scanf("%lf",&addHydrogen);
            if (addHydrogen>=0) {
                break;
            } else {
                printf("Has to be 0 or larger.\n>");
            }
        }

        if (addHydrogen > tank->maxAmountKg-tank->hydrogenAmountKg) {
            printf("Only room for %.lf kg\n", tank->maxAmountKg - tank->hydrogenAmountKg);
        }
        increaseTank(tank, addHydrogen);
        printf("The new status of the tank is:\n");
        printTankStatus(tank);
    } else {
        printf("Tank is already full.\n");
    }
}

