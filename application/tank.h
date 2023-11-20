
#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED
#include"structs.h"
#endif
double isTankFull (hydrogenTank* tank);
double tankFreeSpace(hydrogenTank* tank);
int isValidIncreaseOfHydrogen(hydrogenTank* tank, double amountIncrease);

double convertElectricityToHydrogen(double electricityMWh);
double tankPercentageFull(hydrogenTank* tank);
void printVirtualTank(hydrogenTank* tank);
void increaseTank(hydrogenTank* tank, double kg);
void decreaseTank(hydrogenTank* tank, double kg);
void printTankStatus(hydrogenTank* tank);
void increaseTotalAmountOfExcessElectricity (hydrogenTank* tank, double MwH);
void increaseTotalAmountOfHydrogenProduced(hydrogenTank* tank, double kg);