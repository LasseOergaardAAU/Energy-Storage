#include "functions.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "dataCaller.h"
#include "structs.h"
#include "dates.h"

double getGrossConsumption(date inputDate) {
    char buffer[1000];
    char *data;
    double result = 0;

    FILE *filePointer = fopen("EPAC.csv", "r");

    if (filePointer == NULL) {
        exit(-1);
    }

    // Finds the line of which the data is, based on hour difference.
    int lines = dateToLine(inputDate);

    for (int i = 0; i < lines + 1; ++i) {
        // Gets next line
        fgets(buffer, sizeof(buffer), filePointer);
    }

    data = strtok(buffer, ";");

    // Gets column of gross consumption.
    for (int i = 0; i < 20; ++i) {
        //Gets next column

        data = strtok(NULL, ";");
    }

    // Data digits are seperated by "," and not ".", so this is replaced
    for (int i = 0; i < strlen(data); ++i) {
        if (data[i] == ',') {
            data[i] = '.';
            break;
        }
    }
    result += strtod(data, NULL);

    fgets(buffer, sizeof(buffer), filePointer);
    data = strtok(buffer, ";");
    for (int i = 0; i < 20; ++i) {
        data = strtok(NULL, ";");
    }

    for (int i = 0; i < strlen(data); ++i) {
        if (data[i] == ',') {
            data[i] = '.';
            break;
        }
    }

    result += strtod(data, NULL);
    fclose(filePointer);

    return result;
}

double getGrossProduction(date inputDate) {
    char buffer[1000];
    char *data;
    double result = 0;

    FILE *filePointer = fopen("EPAC.csv", "r");

    if (filePointer == NULL) {
        exit(-1);
    }

    int lines = dateToLine(inputDate);

    for (int i = 0; i < lines; ++i) {
        // Gets next line
        fgets(buffer, sizeof(buffer), filePointer);
    }

    data = strtok(buffer, ";");
    data = strtok(NULL, ";");
    data = strtok(NULL, ";");
    for (int i = 0; i < 14; ++i) {
        for (int j = 0; j < strlen(data); ++j) {
            if (data[j] == ',') {
                data[j] = '.';
                break;
            }
        }

        result += strtod(data, NULL);
        data = strtok(NULL, ";");
    }

    fgets(buffer, sizeof(buffer), filePointer);
    data = strtok(buffer, ";");
    data = strtok(NULL, ";");
    data = strtok(NULL, ";");

    for (int i = 0; i < 14; ++i) {
        for (int j = 0; j < strlen(data); ++j) {
            if (data[j] == ',') {
                data[j] = '.';
                break;
            }
        }
        result += strtod(data, NULL);
        data = strtok(NULL, ";");
    }
    fclose(filePointer);
    return result;
}

double getGrossGridLoss(date inputDate) {
    char buffer[1000];
    char *data;
    double result = 0;

    FILE *filePointer = fopen("EPAC.csv", "r");

    if (filePointer == NULL) {
        exit(-1);
    }

    int lines = dateToLine(inputDate);

    for (int i = 0; i < lines + 1; ++i) {
        // Gets next line
        fgets(buffer, sizeof(buffer), filePointer);
    }

    data = strtok(buffer, ";");
    for (int i = 0; i < 21; ++i) {
        data = strtok(NULL, ";");
    }


    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < strlen(data); ++j) {
            if (data[j] == ',') {
                data[j] = '.';
                break;
            }
        }
        result += strtod(data, NULL);
        data = strtok(NULL, ";");
    }

    fgets(buffer, sizeof(buffer), filePointer);
    data = strtok(buffer, ";");
    for (int i = 0; i < 21; ++i) {
        data = strtok(NULL, ";");
    }


    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < strlen(data); ++j) {
            if (data[j] == ',') {
                data[j] = '.';
                break;
            }
        }
        result += strtod(data, NULL);
        data = strtok(NULL, ";");

    }


    fclose(filePointer);

    return result;
}

char *dataStringToHour(char *dataString) {
    char *destination;
    char *tempTimeStr = strdup(dataString);
    char *dateStr = strtok(tempTimeStr, ";");
    tempTimeStr = strtok(dateStr, " ");
    destination = strtok(NULL, ";");

    return destination;
}


