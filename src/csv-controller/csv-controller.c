#include "../common-headers.h"
unsigned int rowNo = 0;
unsigned int columnNo = 0;

void incrementRow()
{
    rowNo++;
}

void incrementColumn()
{
    columnNo++;
}

void resetColumn()
{
    columnNo = 0;
}

void addEntry(char *entry)
{

    printf("Entry %s (%d,%d)\n", entry, rowNo, columnNo);
}