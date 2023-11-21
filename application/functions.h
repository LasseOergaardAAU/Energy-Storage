
#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED
#include"structs.h"
#endif

void runApplication();
int isValidInput(char input[], char* commands[], int commandsLength);
void doNextOperation(char input[], hydrogenTank* tank, char* commands[], int commandsLength);
void runSimulation(hydrogenTank* tank);
void printHydrogen(date inputDate);
double exceedingElectricity(date inputDate, hydrogenTank tank);
void printCommands(char *commands[], int arrLength);
void printData(date inputDate);
