#include "functions.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "dataCaller.h"
#include "time.h"

// Takes a date, and return the gross consumption of the date.
double getGrossConsumption(date inputDate) {
    char buffer[1000];
    char *data;
    double result = 0;
    FILE *filePointer = fopen("EPAU.csv", "r");

    if (filePointer == NULL) {
        exit(-1);
    }

    //finds and goes to the line of which the data is in csv file.
    int lines = dateToLine(inputDate);


    for (int i = 0; i < lines + 1; ++i) {
        fgets(buffer, sizeof(buffer), filePointer);
    }

    data = strtok(buffer, ";");

    //gets column of gross consumption.
    for (int i = 0; i < 20; ++i) {
        data = strtok(NULL, ";");
    }


    //data digits are seperated by "," and not ".", so this is replaced to make it to a double.
    for (int i = 0; i < strlen(data); ++i) {
        if (data[i] == ',') {
            data[i] = '.';
            break;
        }
    }
    result += strtod(data, NULL);

    // Does this again for the next row, as the next row is another zone in Denmark.
    fgets(buffer, sizeof(buffer), filePointer);
    data = strtok(buffer, ";");
    for (int i = 0; i < 20; ++i) {
        data = strtok(NULL, ";");
    }
    result += strtod(data, NULL);
    fclose(filePointer);

    return result;
}

//Gets the gross production on a specific date.
double getGrossProduction(date inputDate) {
    char buffer[1000];
    char *data;
    double result = 0;

    FILE *filePointer = fopen("EPAU.csv", "r");

    if (filePointer == NULL) {
        exit(-1);
    }
    //Find the line of which the data is on, and goes to it.
    int lines = dateToLine(inputDate);

    for (int i = 0; i < lines; ++i) {
        //gets next line
        fgets(buffer, sizeof(buffer), filePointer);
    }

    // Goes to the column of which the production data starts.
    data = strtok(buffer, ";");
    data = strtok(NULL, ";");
    data = strtok(NULL, ";");

    //replaces , with . so it can be made into a double later.
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

    // Does the same to the next line.
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

    return result;
}

// Takes a line on the data set, and tells the date on that line.
date lineToDate(int line) {
    char buffer[1000];
    char *data;
    date dateResult;

    FILE *filePointer = fopen("EPAU.csv", "r");


    for (int i = 0; i < line + 1; ++i) {
        fgets(buffer, sizeof(buffer), filePointer);
    }
    char temp[1000];
    strcpy(temp, buffer);

    data = strtok(temp, ";");
    char *leftDate = strtok(data, "T");

    char *token = strtok(leftDate, "-");
    dateResult.year = atoi(token);

    token = strtok(NULL, "-");
    dateResult.month = atoi(token);

    token = strtok(NULL, "-");
    dateResult.day = atoi(token);

    token = strtok(buffer, ";");
    token = strtok(buffer, " ");
    token = strtok(NULL, " ");
    token = strtok(token, ":");
    dateResult.hour = atoi(token);

    return dateResult;
}

//Takes a date, and tells which line it is on, in the data set.
int dateToLine(date inputDate) {
    char buffer[1000];
    char *data;
    date startDate;

    FILE *filePointer = fopen("EPAU.csv", "r");

    fgets(buffer, sizeof(buffer), filePointer);
    fgets(buffer, sizeof(buffer), filePointer);

    char temp[1000];
    strcpy(temp, buffer);

    data = strtok(temp, ";");
    char *leftDate = strtok(data, "T");
    char *rightDate = strtok(NULL, "T");

    char *token = strtok(leftDate, "-");
    startDate.year = atoi(token);

    token = strtok(NULL, "-");
    startDate.month = atoi(token);

    token = strtok(NULL, "-");
    startDate.day = atoi(token);

    token = strtok(buffer, ";");
    token = strtok(buffer, " ");
    token = strtok(NULL, " ");
    token = strtok(token, ":");
    startDate.hour = atoi(token);

    int hours = hoursBetween(inputDate, startDate);

    return hours * 2 + 1;
}


// gets the gross grid loss, on a date.
double getGrossGridLoss(date inputDate) {
    char buffer[1000];
    char *data;
    double result = 0;

    FILE *filePointer = fopen("EPAU.csv", "r");

    if (filePointer == NULL) {
        exit(-1);
    }

    //finds the line of which the data is on.
    int lines = dateToLine(inputDate);

    for (int i = 0; i < lines + 1; ++i) {
        //gets next line
        fgets(buffer, sizeof(buffer), filePointer);
    }

    //goes to the column of which the data starts.
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
        printf("%s ", data);
        result += strtod(data, NULL);
        data = strtok(NULL, ";");
    }

    //Does this for the next line too.
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
        printf("%s ", data);
        result += strtod(data, NULL);
        data = strtok(NULL, ";");
    }

    return result;
}

//Returns the amount of hours between two dates.
int hoursBetween(date date1, date date2) {

    char dateStr1[20]; // end
    char dateStr2[20]; // beginning

    snprintf(dateStr1, sizeof(dateStr1), "%d-%d-%d %d:00:00", date1.year, date1.month, date1.day, date1.hour);
    snprintf(dateStr2, sizeof(dateStr2), "%d-%d-%d %d:00:00", date2.year, date2.month, date2.day, date2.hour);

    struct tm tm1, tm2;
    memset(&tm1, 0, sizeof(struct tm));
    memset(&tm2, 0, sizeof(struct tm));

    sscanf(dateStr1, "%d-%d-%d %d:%d:%d", &tm1.tm_year, &tm1.tm_mon, &tm1.tm_mday,
           &tm1.tm_hour, &tm1.tm_min, &tm1.tm_sec);

    sscanf(dateStr2, "%d-%d-%d %d:%d:%d", &tm2.tm_year, &tm2.tm_mon, &tm2.tm_mday,
           &tm2.tm_hour, &tm2.tm_min, &tm2.tm_sec);

// Adjust tm_year and tm_mon values
    tm1.tm_year -= 1900;
    tm1.tm_mon -= 1;

    tm2.tm_year -= 1900;
    tm2.tm_mon -= 1;

    // Convert struct tm objects to time in seconds
    time_t time1 = mktime(&tm1);
    time_t time2 = mktime(&tm2);

    // Calculate time difference in seconds
    time_t diff = difftime(time2, time1);

    // Convert time difference to hours
    int hours = diff / 3600;

    return hours;
}

