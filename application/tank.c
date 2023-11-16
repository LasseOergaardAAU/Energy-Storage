#include "tank.h"
#include <stdio.h>
#include "functions.h"
#include <stdlib.h>
#include <math.h>


//This funktion finds out if the tank full
double isFull(hydrogenTank tank) {
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


//En funktion der tager imod 2 datoer, return 1 true hvis den første er tidligere
int isDateEarlier(date date1, date date2) {

    if ((date1.year < date2.year) ||
        (date1.year == date2.year && date1.month < date2.month) ||
        (date1.year == date2.year && date1.month == date2.month && date1.day < date2.day) ||
        (date1.year == date2.year && date1.month == date2.month && date1.day < date2.day && date1.hour < date2.hour)) {
        return 1;
    } else {
        return 0;
    }
}





