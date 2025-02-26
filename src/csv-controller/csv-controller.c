/* This file receives data from csv.y and send it to csv-data.c */

#include "../common-headers.h"
#include "csv-controller.h"
#include "csv-data.h"
unsigned int rowNo = 1;
unsigned int columnNo = 1;

void incrementColumn()
{
    columnNo++;
}

void nextRow()
{
    columnNo = 0;
    rowNo++;
}

void addEntry(char *entry, int entryType)
{
    switch (entryType)
    {
    case NUM:
        // printf("Num %s r%d:c%d\n", entry, rowNo, columnNo);
        addNumValue(atof(entry), rowNo, columnNo);
        break;
    case STR:
        // printf("Str '%s' r%d:c%d\n", entry, rowNo, columnNo);
        addStrValue(entry, rowNo, columnNo);
        break;

    default:
        fprintf(stderr, "Invalid Entry Type %d\n", entryType);
        exit(1);
        break;
    }
}

void csvProgramStart()
{
    initializeCSVDatabase();
}

void csvProgramEnd()
{
    createCSVDatabase();
}