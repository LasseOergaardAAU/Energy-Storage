#include "functions.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "dataCaller.h"
#include "time.h"


double getGrossConsumption(date inputDate) {
    char buffer[1000];
    char *data;
    FILE *filePointer = fopen("EPAU.csv", "r");

    if (filePointer == NULL) {
        exit(-1);
    }

    for (int i = 0; i < dateToLine(inputDate); ++i) {
        //gets next line
        fgets(buffer, sizeof(buffer), filePointer);
    }

    data = strtok(buffer, ",");

    //gets column of grossconsumption.
    for (int i = 0; i < 22; ++i) {
        //Gets next column
        data = strtok(NULL, ",");
    }
    printf("%s\n", data);

    fclose(filePointer);
}

int dateToLine(date inputDate) {
    char buffer[1000];
    char *data;
    date startDate;

    FILE *filePointer = fopen("EPAU.csv", "r");

    fgets(buffer, sizeof(buffer), filePointer);
    fgets(buffer, sizeof(buffer), filePointer);

    data = strtok(buffer, ",");
    char *leftDate = strtok(data, "T");
    char *rightDate = strtok(NULL, "T");

    char *token = strtok(leftDate, "-");
    startDate.year = atoi(token);

    token = strtok(NULL, "-");
    startDate.month = atoi(token);

    token = strtok(NULL, "-");
    startDate.day = atoi(token);

    token = strtok(rightDate, ":");
    startDate.hour = atoi(token);

    hoursBetween(startDate, startDate);
}

int hoursBetween(date date1, date date2) {

    char time1[20]; // end
    char time2[20]; // beginning
    double time_Diff; // Difference
    char *endPart;
    snprintf(time1, sizeof(time1), "%d/%d/%d %d:00:00", date1.year, date1.month, date1.day, date1.hour);
    snprintf(time2, sizeof(time2), "%d/%d/%d %d:00:00", date2.year, date2.month, date2.day, date2.hour);
    strtol(time1,&endPart,10);
    strtol(time,&endPart,10);
    time(&time1);
    time(time2);
    time_Diff = (difftime(time2, time1) / 3600);

}