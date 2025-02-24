/* This file receives data from csv.y and send it to csv-data.c */

#include "../common-headers.h"
#include "csv-controller.h"
unsigned int rowNo = 0;
unsigned int columnNo = 0;

void incrementColumn()
{
    columnNo++;
}

void nextRow()
{
    columnNo = 0;
    rowNo++;
}

void addEntry(char *entry)
{
    printf("Entry %s (%d,%d)\n", entry, rowNo, columnNo);
}