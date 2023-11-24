
#ifndef ENERGY_STORAGE_STRUCTS_H
#define ENERGY_STORAGE_STRUCTS_H
typedef struct hydrogenTank{
    double hydrogenAmountKg;
    double totalElectricityUsedMwH;
    double totalAmountOfHydrogenProducedKg;
    double maxAmountKg;
    double electricityMadeByHydrogenMwH;
} hydrogenTank;

typedef struct date {
    int year;
    int month;
    int day;
    int hour;
} date;
#define MWH_PER_KG_HYDROGEN 0.040
#define EL_TO_H_CONV_RATE 0.7
#define H_TO_EL_CONV_RATE 0.7
#define MINIMUM_TANK_PERCENTAGE_FULL 30
#endif //ENERGY_STORAGE_STRUCTS_H
