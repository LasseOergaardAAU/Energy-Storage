
#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED
#include"structs.h"
#endif
double isFull (hydrogenTank tank);
double tankFreeSpace(hydrogenTank tank);
int isValidIncreaseOfHydrogen(hydrogenTank tank, double amountIncrease);

double convertElectricityToHydrogen(double electricityMWh);
double tankPercentageFull(hydrogenTank tank);
void printVirtualTank(hydrogenTank tank);
hydrogenTank increaseTank(hydrogenTank tank, double kg);
hydrogenTank decreaseTank(hydrogenTank tank, double kg);
void printTankStatus(hydrogenTank tank);