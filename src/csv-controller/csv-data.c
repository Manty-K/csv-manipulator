#include "../common-headers.h"
#include "csv-data.h"
#include "../output/output.h"
#include "../data-structures/data-structures.h"

ARRAY *csvDatabase;
QUEUE *dataQueue;

typedef struct csvRow
{
    unsigned int rowNo;
    ARRAY *row;
} CSV_ROW;

typedef struct csvCol
{
    unsigned int colNo;
    CSV_DATA *data;
} CSV_COL;

void initializeCSVDatabase()
{
    csvDatabase = createArray(1);
    dataQueue = createQueue();
}

void addCSVDataToQueue(CSV_DATA *data)
{
    enqueue(dataQueue, data);
}

void createCSVDatabase()
{
    int index = -1;
    ARRAY *r;
    unsigned int current = 0;

    while (!isEmptyQueue(dataQueue))
    {
        CSV_DATA *data = dequeue(dataQueue);

        if (index == -1 || current != data->rowNo)
        {
            r = createArray(1);
            current = data->rowNo;
            appendArray(csvDatabase, r);
            index++;
        }

        appendArray(getElementArray(csvDatabase, index), data);
    }

    freeQueue(dataQueue);
}

void addNumValue(float val, unsigned int row, unsigned int col)
{
    CSV_DATA *csvData = malloc(sizeof(CSV_DATA));
    csvData->valueType = NUM_TYPE;
    csvData->value.f = val;
    csvData->rowNo = row;
    csvData->colNo = col;

    addCSVDataToQueue(csvData);
}

void addStrValue(char *val, unsigned int row, unsigned int col)
{
    CSV_DATA *csvData = malloc(sizeof(CSV_DATA));
    csvData->valueType = STR_TYPE;
    csvData->value.s = val;
    csvData->rowNo = row;
    csvData->colNo = col;

    addCSVDataToQueue(csvData);
}

void displayCSVDATA(CSV_DATA *data)
{
    switch (data->valueType)
    {
    case NUM_TYPE:
        printf("Num %.1f r%d:c%d\n", data->value.f, data->rowNo, data->colNo);
        break;
    case STR_TYPE:
        printf("Str '%s' r%d:c%d\n", data->value.s, data->rowNo, data->colNo);
        break;

    default:
        fprintf(stderr, "Invalid Entry Type %d\n", data->valueType);
        exit(1);
        break;
    }
}

void repeatPrintStr(char *str, unsigned int count)
{
    for (unsigned int i = 0; i < count; i++)
    {
        appendFile(str);
    }
}

void displayDatabase()
{
    unsigned int currentRowIndex = 1;
    unsigned int currentColIndex;
    unsigned int size;

    for (unsigned int i = 0; i < getArraySize(csvDatabase); i++)
    {
        currentColIndex = 1;
        size = getArraySize(getElementArray(csvDatabase, i));

        for (unsigned int j = 0; j < size; j++)
        {
            CSV_DATA *data = getElementArray(getElementArray(csvDatabase, i), j);
            displayCSVDATA(data);

            if (data->rowNo > currentRowIndex)
            {
                repeatPrintStr("\n", data->rowNo - currentRowIndex);
                currentRowIndex = data->rowNo;
            }
            if (currentColIndex < data->colNo)
            {
                repeatPrintStr(",", data->colNo - currentColIndex);
                currentColIndex = data->colNo;
            }

            if (data->valueType == STR_TYPE)
            {
                appendFile("%s", data->value.s);
            }

            if (data->valueType == NUM_TYPE)
            {
                appendFile("%.1f", data->value.f);
            }
        }
    }
}

void processOutput()
{
    displayDatabase();
}
