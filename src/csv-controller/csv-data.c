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

void displayDatabase()
{
    for (unsigned int i = 0; i < getArraySize(csvDatabase); i++)
    {
        unsigned int size = getArraySize(getElementArray(csvDatabase, i));

        for (unsigned int j = 0; j < size; j++)
        {
            CSV_DATA *data = getElementArray(getElementArray(csvDatabase, i), j);

            if (data->valueType == STR_TYPE)
            {
                printf("\"%s\"", data->value.s);
            }

            if (data->valueType == NUM_TYPE)
            {
                printf("%.1f", data->value.f);
            }

            printf(j + 1 != size ? ", " : "");
        }
        printf("\n");
    }
}

void processOutput()
{
    displayDatabase();
    appendFile("1,2,3");
}
