#ifndef ENERGY_STORAGE_DATES_H
#define ENERGY_STORAGE_DATES_H
#include "structs.h"
#endif //ENERGY_STORAGE_DATES_H
int isDateEarlier(date date1, date date2);
int isDateValid(date inputDate);
date getLastDate();
void printDate(date inputDate);
date scanDate();
int dateToLine(date inputDate);
int hoursBetween(date date1, date newestDate);
date lineToDate(int line);
date getFirstDate();
int isDateReal(date inputDate);
date stringToDate(char str[]);