
#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED
#include"structs.h"
#endif
#define KWH_PER_KG_HYDROGEN 52.5



void runApplication();
int isValidInput(char input[]);
void doNextOperation(char input[], hydrogenTank tank);
double tankPercentageFull(hydrogenTank tank);
void printTank(hydrogenTank tank);
hydrogenTank increaseTank(hydrogenTank tank, double kg);
hydrogenTank decreaseTank(hydrogenTank tank, double kg);
void runSimulation();
void printDate(date inputDate) ;
void printHydrogen(date inputDate);
double exceedingElectricity(date inputDate, hydrogenTank tank);
date scanDate();
