#include "testAll.h"

int main() {
    // Tank tests
    testIsTankFull();
    testIsTankNotFull();
    testTankFreeSpace();
    testIsValidIncreaseOfHydrogen();
    testConvertElectricityToHydrogen();
    testTankPercentageFull();
    testIncreaseTank();
    testDecreaseTank();
    testIncreaseTotalAmountOfExcessElectricity();
    testIncreaseTotalAmountOfHydrogenProduced();
    testCalculateExcessEnergy();
    testConvertHydrogenToElectricity();
    testResetTank();
    testConvertTank();
    testFillTank();

    // DataCaller tests:
    testGetGrossConsumption();
    testGetGrossProduction();
    testGetGrossGridLoss();
    testDataStringToHour();

    // Functions tests:
    testIsValidInput();

    // Dates tests:
    testIsDateEarlier();
    testIsDateValid();
    testGetLastDate();
    testGetFirstDate();
    testIsDateReal();
    testLineToDate();
    testDateToLine();
    testHoursBetween();
    testStringToDate();

    return 0;
}
