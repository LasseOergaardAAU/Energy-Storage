#include "../application/tank.h"
#include "assert.h"

void testIsTankFull(void) {
    // Assign
    hydrogenTank tank =  {100,0,100,100,0};
    int expected = 1;
    int result;
    // Act
    result = isTankFull(&tank);

    // Assert
    assert(expected == result);
}

void testIsTankNotFull(void) {
    // Assign
    hydrogenTank tank =  {50,0,100,100,0};
    int expected = 0;
    int result;
    // Act

    result = isTankFull(&tank);

    // Assert
    assert(expected == result);
}

void testTankFreeSpace(void) {

}

void testIsValidIncreaseOfHydrogen(void) {

}

void testConvertElectricityToHydrogen(void) {

}

void testTankPercentageFull(void) {

}

void testIncreaseTank(void) {

}

void testDecreaseTank(void) {

}

void testIncreaseTotalAmountOfExcessElectricity(void) {

}

void testIncreaseTotalAmountOfHydrogenProduced(void) {

}

void testCalculateExcessEnergy(void) {

}
void testConvertHydrogenToElectricity(void) {

}

void testResetTank(void) {

}

void testConvertTank(void) {

}

void testFillTank(void) {

}