
#ifndef ENERGY_STORAGE_STRUCTS_H
#define ENERGY_STORAGE_STRUCTS_H
typedef struct hydrogenTank{
    double hydrogenAmountKg;
    double totalElectricityUsedKwH;
    double totalAmountOfHydrogenProducedKg;
    double maxAmountKg;
} hydrogenTank;

typedef struct date {
    int year;
    int month;
    int day;
    int hour;
} date;
#endif //ENERGY_STORAGE_STRUCTS_H
