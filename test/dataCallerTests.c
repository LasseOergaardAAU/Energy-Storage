#include "../application/dataCaller.h"
#include "../application/structs.h"
#include "assert.h"
#include "math.h"

void testGetGrossConsumption(void) {
    // Assign
    date newDate =  {2023,11,3,10};
    double expected = 4991.85;
    double result;
    // Act
    result = getGrossConsumption(newDate);
    result = round(result*100)/100;

    // Assert
    assert(expected == result);
}

void testGetGrossProduction(void) {

}

void testGetGrossGridLoss(void) {

}

void testDataStringToHour(void) {

}