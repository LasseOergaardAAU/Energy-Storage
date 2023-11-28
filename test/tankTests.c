#include "../application/tank.h"
#include "assert.h"
#include "math.h"

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
    // Assign
    hydrogenTank tank =  {50,0,100,100,0};

    double result;
    double expected = 50;

    //Act
    result = tankFreeSpace(&tank);

    //Assert
    assert(result == expected);
}

void testIsValidIncreaseOfHydrogen(void) {
    // Assign
    hydrogenTank tank =  {50,0,100,100,0};
    double amountIncrease = 30;

    int result;
    int expected = 1;

    //Act
    result = isValidIncreaseOfHydrogen(&tank, amountIncrease);

    //Assert
    assert(result == expected);
}

void testConvertElectricityToHydrogen(void) {
    // Assign
    double electricityMWh = 1000;

    double result;
    double expected = (electricityMWh / MWH_PER_KG_HYDROGEN) * EL_TO_H_CONV_RATE;

    //Act
    result =convertElectricityToHydrogen(electricityMWh);

    //Assert
    assert(result == expected);
}

void testTankPercentageFull(void) {
    // Assign
    hydrogenTank tank =  {50,0,100,100,0};

    double result;
    double expected = 50;

    //Act
    result = tankPercentageFull(&tank);

    //Assert
    assert(result == expected);
}

void testIncreaseTank(void) {
    // Assign
    hydrogenTank tank =  {50,0,100,100,0};
     double kg = 30;

     double expected = 80;

    //Act
    increaseTank(&tank, kg);

    //Assert
    assert(tank.hydrogenAmountKg == expected);
}

void testDecreaseTank(void) {
    // Assign
    hydrogenTank tank =  {50,0,100,100,0};
    double kg = 30;

    double expected = 20;

    //Act
    decreaseTank(&tank, kg);

    //Assert
    assert(tank.hydrogenAmountKg == expected);
}

void testIncreaseTotalAmountOfExcessElectricity(void) {
    // Assign
    hydrogenTank tank =  {50,0,100,100,0};
    double MwH = 400;

    double expected = 400;

    //Act
    increaseTotalAmountOfExcessElectricity(&tank, MwH);

    //Assert
    assert(tank.totalElectricityUsedMwH == expected);
}

void testIncreaseTotalAmountOfHydrogenProduced(void) {
    // Assign
    hydrogenTank tank =  {50,0,100,100,0};
    double kg = 50;

    double expected = 150;

    //Act
    increaseTotalAmountOfHydrogenProduced(&tank, kg);

    //Assert
    assert(tank.totalAmountOfHydrogenProducedKg == expected);
}

void testCalculateExcessEnergy(void) {
    // Assign
    date newDate = {2023,1,1,9};

    double result;
    double expected = 290.58;

    //Act
    result = round(calculateExcessEnergy(newDate)*100)/100;

    //Assert
    assert(result == expected);
}
void testConvertHydrogenToElectricity(void) {
    double hydrogenKg = 1000;

    double result;
    double expected = (hydrogenKg * MWH_PER_KG_HYDROGEN) * H_TO_EL_CONV_RATE;

    //Act
    result = convertHydrogenToElectricity(hydrogenKg);

    //Assert
    assert(result == expected);
}

void testResetTank(void) {
    // Assign
    hydrogenTank tank =  {50,0,100,100,0};
    hydrogenTank expected = {0,0,0,0,0};

    //Act
    resetTank(&tank);

    //Assert
}

void testConvertTank(void) {
    // Assign
    hydrogenTank tank = {100,0,100,100,0};
    double expected = 100*MWH_PER_KG_HYDROGEN*0.7;

    //Act
    convertTank(&tank);

    //Assert
    assert(expected == tank.electricityMadeByHydrogenMwH);
}