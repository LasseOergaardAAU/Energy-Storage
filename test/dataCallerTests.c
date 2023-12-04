#include "../application/dataCaller.h"
#include "../application/structs.h"
#include "assert.h"
#include "math.h"
#include "stdio.h"
#include "string.h"

void testGetGrossConsumption(void) {
    // Assign
    date newDate = {2023, 11, 3, 10};
    double expected = 4991.85;
    double result;
    // Act
    result = getGrossConsumption(newDate);
    result = round(result * 100) / 100;

    // Assert
    assert(expected == result);
}

void testGetGrossProduction(void) {
    // Assign
    date newDate = {2023, 11, 3, 15};
    double expected = 1446.16;
    double result;

    //Act
    result = getGrossProduction(newDate);
    result = round(result * 100) / 100;

    //Assert
    assert(expected == result);
}

void testGetGrossGridLoss(void) {
    // Assign
    date newDate = {2023, 10, 4, 5};
    double expected = 434.03;
    double result;

    //Act
    result = getGrossGridLoss(newDate);
    result = round(result * 100) / 100;

    //Assert
    assert(expected == result);
}

void testDataStringToHour(void) {
    // Assign
    char buffer[1000];
    FILE *fp = fopen("EPAC.csv", "r");

    char *expected = "08:00"; // For line 30
    char *result;

    //Act
    for (int i = 0; i < 30; ++i) {
        fgets(buffer, sizeof(buffer), fp);
    }
    result = dataStringToHour(buffer);

    //Assert
    fclose(fp);
    assert(strcmp(result, expected) == 0);
}