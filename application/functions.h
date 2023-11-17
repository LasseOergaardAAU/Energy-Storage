
#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED
#include"structs.h"
#endif

void runApplication();
int isValidInput(char input[], char* commands[], int commandsLength);
void doNextOperation(char input[], hydrogenTank tank, char* commands[], int commandsLength);
hydrogenTank runSimulation(date startDate, date endDate, hydrogenTank tank);
void printHydrogen(date inputDate);
double exceedingElectricity(date inputDate, hydrogenTank tank);
date scanDate();
