#include "../common-headers.h"
#include "csv-data.h"
#include "../output/output.h"

void initializeCSVDatabase()
{
}

void addCSVDataToDatabase(CSV_DATA *data)
{
}

void addNumValue(float val, unsigned int row, unsigned int col)
{
    CSV_DATA *csvData = malloc(sizeof(CSV_DATA));
    csvData->valueType = NUM_TYPE;
    csvData->value.f = val;
    csvData->rowNo = row;
    csvData->colNo = col;

    addCSVDataToDatabase(csvData);
}

void addStrValue(char *val, unsigned int row, unsigned int col)
{
    CSV_DATA *csvData = malloc(sizeof(CSV_DATA));
    csvData->valueType = STR_TYPE;
    csvData->value.s = val;
    csvData->rowNo = row;
    csvData->colNo = col;

    addCSVDataToDatabase(csvData);
}

void processOutput()
{
    appendFile("1,2,3");
}
