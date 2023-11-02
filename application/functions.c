#include "functions.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"

void runApplication() {
    while (1) {
        printf("Write a command.\n>");
        char input[30];
        scanf("%s", input);
        strlwr(input);
        if (!isValidInput(input)) {
            printf("Invalid input. Try again\n");
            continue;
        }
        doNextOperation(input);
    }
}

void doNextOperation(char input[]) {
    if (strcmp(input, "quit") == 0) {
        printf("Quitting the application.");
        exit(0);
    } else if (strcmp(input, "help") == 0) {
        printf("Here you have the different commands that you can input: \n>status\n>quit\n>graph\n>table\n>prognosis\n>hydrogen");
    } else if (strcmp(input, "status") == 0) {
        printf("The status of the tank is:");
    }
}

int isValidInput(char input[]) {
    if (strcmp(input, "quit") == 0) {
        return 1;
    } else if (strcmp(input, "help") == 0) {
        return 1;
    } else if (strcmp(input, "status") == 0) {
        return 1;
    }else if (strcmp(input, "graph") == 0) {
        return 1;
    } else if (strcmp(input, "table") == 0) {
        return 1;
    }else if (strcmp(input, "hydrogen") == 0) {
        return 1;
    } else if (strcmp(input, "prognosis") == 0) {
        return 1;
    } else {
        return 0;
    }
}
