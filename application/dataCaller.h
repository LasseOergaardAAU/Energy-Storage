#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED
#include"structs.h"
#endif
double getGrossConsumption(date inputDate);
int dateToLine(date inputDate);
int hoursBetween(date date1, date newestDate);
double getGrossProduction(date inputDate);
double getGrossGridLoss(date inputDate);
date lineToDate(int line);