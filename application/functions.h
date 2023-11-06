#define KWH_PER_KG_HYDROGEN 52.5

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

void runApplication();
int isValidInput(char input[]);
void doNextOperation(char input[], hydrogenTank tank);
double tankPercentageFull(hydrogenTank tank);
void printTankStatus(hydrogenTank tank);
hydrogenTank increaseTank(hydrogenTank tank, double kg);
hydrogenTank decreaseTank(hydrogenTank tank, double kg);
void runSimulation();
void printDate(date inputDate) ;
void printHydrogen(date inputDate);
double exceedingElectricity(date inputDate, hydrogenTank tank);