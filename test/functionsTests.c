#include "../application/functions.h"
#include "assert.h"

void testIsValidInput(void) {
    // Assign
    char input[] = "help";
    char *commands[] = {"help", "test"};
    int arrLength = 2;

    int result;
    int expected = 1;

    //Act
    result = isValidInput(input, commands, arrLength);

    //Assert
    assert(result == expected);
}