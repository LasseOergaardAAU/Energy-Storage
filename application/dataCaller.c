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

    int lines = dateToLine(inputDate);

    for (int i = 0; i < lines; ++i) {
        //gets next line
        fgets(buffer, sizeof(buffer), filePointer);
    }

    data = strtok(buffer, ";");

    //gets column of grossconsumption.
    for (int i = 0; i < 22; ++i) {
        //Gets next column
        data = strtok(NULL, ";");
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

    return hours*2+2;
}

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