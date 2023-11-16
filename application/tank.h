
#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED
#include"structs.h"
#endif
double isFull (hydrogenTank tank);
double tankFreeSpace(hydrogenTank tank);
int isValidIncreaseOfHydrogen(hydrogenTank tank, double amountIncrease);
int isDateEarlier(date date1, date date2);
int isDateValid(date inputDate);
int getLastDate();