#include "../application/dates.h"
#include "assert.h"
#include "stdio.h"
#include "stdlib.h"

void testIsDateEarlier(void) {
    // Assign
    date earliestDate = {2023, 2, 20, 5};
    date latestDate = {2023, 4, 20, 0};
    int expected = 1;
    int result;

    //Act
    result = isDateEarlier(earliestDate, latestDate);

    //Assert
    assert(result == expected);
}


void testIsDateValid(void) {
    // Assign
    date validDate = {2023, 1, 10, 15};
    int expected = 1;
    int result;

    //Act
    result = isDateValid(validDate);

    //Assert
    assert(result == expected);
}


void testGetFirstDate(void) {
    // Assign
    char buffer[1000];
    FILE *fp = fopen("EPAU.csv", "r");

    fgets(buffer, sizeof(buffer), fp);
    fgets(buffer, sizeof(buffer), fp);

    date firstDate = stringToDate(buffer);
    date resultDate;

    //Act
    resultDate = getFirstDate();

    //Assert
    assert(firstDate.year == resultDate.year);
    assert(firstDate.month == resultDate.month);
    assert(firstDate.day == resultDate.day);
    assert(firstDate.hour == resultDate.hour);
}

void testIsDateReal(void) {
    // Assign
    date fakeDate = {2023, 13, 1, 1};
    int result;
    int expected = 0;

    //Act
    result = isDateReal(fakeDate);

    //Assert
    assert(result == expected);
}

void testDateToLine(void) {
    // Assign
    date newDate = {2023, 5, 4, 10};
    int result;
    int expected = 8809;

    //Act
    result = dateToLine(newDate);

    //Assert
    assert(result == expected);
}

void testHoursBetween(void) {
    // Assign
    date date1 = {2023, 1, 1, 1};
    date date2 = {2023, 2, 2, 2,};

    int result;
    int expected = 1 + 24 + 31 * 24;

    //Act
    result = hoursBetween(date1, date2);

    //Assert
    assert(result == expected);
}

void testStringToDate(void) {
    // Assign
    char testStr[] = "2023-02-04 10:00";

    date resultDate;
    date expectedDate = {2023, 2, 4, 10};

    //Act
    resultDate = stringToDate(testStr);

    //Assert
    assert(resultDate.year == expectedDate.year);
    assert(resultDate.month == expectedDate.month);
    assert(resultDate.day == expectedDate.day);
    assert(resultDate.hour == expectedDate.hour);
}
