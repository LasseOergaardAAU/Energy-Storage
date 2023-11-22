#include "dates.h"
#include "functions.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "dataCaller.h"
#include "time.h"
#include "unistd.h"
#include "structs.h"
#include "tank.h"

//En funktion der tager imod 2 datoer, return 1 true hvis den første er tidligere
int isDateEarlier(date date1, date date2) {
    if ((date1.year < date2.year) ||
        (date1.year == date2.year && date1.month < date2.month) ||
        (date1.year == date2.year && date1.month == date2.month && date1.day < date2.day) ||
        (date1.year == date2.year && date1.month == date2.month && date1.day == date2.day && date1.hour < date2.hour)) {
        return 1;
    } else {
        return 0;
    }
}

// Checking to see if the date is valid or within the bounds of the dataset.
int isDateValid(date inputDate) {
    date firstDate = getFirstDate();
    date lastDate = getLastDate();
    if (isDateEarlier(lastDate, inputDate) == 1 && isDateEarlier(inputDate, firstDate) == 1 && isDateReal(inputDate)) {
        return 1;
    } else {
        return 0;
    }
}

date getLastDate() {
    FILE *file = fopen("EPAU.csv", "r");
    char *data;
    date dateResult;

    if (file == NULL) {
        perror("Error opening file");
        exit(0);
    }

    char buffer[1000]; // Adjust the buffer size as needed

    //sets buffer to the last line in csv file.
    while (fgets(buffer, sizeof(buffer), file) != NULL) {

    }

    dateResult = stringToDate(buffer);

    fclose(file);

    return dateResult;
}

date getFirstDate() {
    FILE *file = fopen("EPAU.csv", "r");
    char *data;
    date dateResult;

    if (file == NULL) {
        perror("Error opening file");
        exit(0);
    }

    char buffer[1000]; // Adjust the buffer size as needed

    fgets(buffer, sizeof(buffer), file);
    fgets(buffer, sizeof(buffer), file);


    dateResult = stringToDate(buffer);

    fclose(file);

    return dateResult;
}

int isDateReal(date inputDate) {
    switch (inputDate.month) {
        case 1:
        case 3:
        case 5:
        case 7:
        case 10:
        case 12:
            if (inputDate.day > 31) {
                return 0;
            }
            break;
        case 4:
        case 6:
        case 8:
        case 11:
            if (inputDate.day > 30) {
                return 0;
            }
            break;
        case 2:
            if (inputDate.day > 28) {
                return 0;
            }
        default:
            break;
    }

    if (inputDate.hour >= 24 || inputDate.hour < 0 || inputDate.month > 12 || inputDate.month < 1) {
        return 0;
    } else {
        return 1;
    };
}

void printDate(date inputDate) {
    printf("%d-%d-%d-%d",
           inputDate.year, inputDate.month,
           inputDate.day, inputDate.hour
    );
}

date scanDate() {
    char dateStr[13];
    date dateStruct;

    //Loop that runs until it get a valid data
    while (1) {
        //Scans for date, and returns date as a struct 'date'.

        scanf("%s", dateStr);

        char *token = strtok(dateStr, "-");
        dateStruct.year = atoi(token);

        token = strtok(NULL, "-");
        dateStruct.month = atoi(token);

        token = strtok(NULL, "-");
        dateStruct.day = atoi(token);

        token = strtok(NULL, "-");
        dateStruct.hour = atoi(token);

        if (isDateValid(dateStruct)) {
            break;
        }
        if(!isDateReal(dateStruct)) {
            printf("Is not a real date");
            printf("\n>");
        } else {
            printf("Date has to be between: ");
            printDate(getFirstDate());
            printf(" & ");
            printDate(getLastDate());
            printf("\n>");
        }
    }

    return dateStruct;
}

// Takes a line, and returns the date corresponding to the line in the dataset.
date lineToDate(int line) {
    char buffer[1000];
    date dateResult;

    FILE *filePointer = fopen("EPAU.csv", "r");


    for (int i = 0; i < line + 1; ++i) {
        fgets(buffer, sizeof(buffer), filePointer);
    }
    dateResult = stringToDate(buffer);
    fclose(filePointer);

    return dateResult;
}

//Takes a date, and find the line it is on, in the dataset.
int dateToLine(date inputDate) {
    char buffer[1000];

    FILE *filePointer = fopen("EPAU.csv", "r");

    fgets(buffer, sizeof(buffer), filePointer);
    fgets(buffer, sizeof(buffer), filePointer);

    date startDate = stringToDate(buffer);

    int hours = hoursBetween(inputDate, startDate);
    fclose(filePointer);

    return hours * 2 + 1;
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

//Tager en string på formen YYYY-MM-DD TT:MM, og laver den om til en date struct.
date stringToDate(char str[]) {
    date dateResult;
    char *data;
    char temp[1000];
    strcpy(temp, str);

    data = strtok(temp, ";");
    char *leftDate = strtok(data, "T");
    char *rightDate = strtok(NULL, "T");

    char *token = strtok(leftDate, "-");
    dateResult.year = atoi(token);

    token = strtok(NULL, "-");
    dateResult.month = atoi(token);

    token = strtok(NULL, "-");
    dateResult.day = atoi(token);

    token = strtok(str, ";");
    token = strtok(str, " ");
    token = strtok(NULL, " ");
    token = strtok(token, ":");
    dateResult.hour = atoi(token);

    return dateResult;
}


