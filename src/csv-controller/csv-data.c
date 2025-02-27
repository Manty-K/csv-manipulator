#include "../common-headers.h"
#include "csv-data.h"
#include "../output/output.h"
#include "../data-structures/data-structures.h"

ARRAY *csvDatabase;
QUEUE *dataQueue;

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
    // printf("CSV data created\n Size: %zu\n", getArraySize(csvDatabase));

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
enum fountOrNot
{
    FOUND,
    NOT_FOUND
};
typedef struct nearOrExact
{
    enum fountOrNot found;
    unsigned int val;
} NearOrExact;

NearOrExact linearSearchNearestRow(unsigned int val)
{
    unsigned int size = getArraySize(csvDatabase);

    NearOrExact ne;
    ne.val = 0;
    ne.found = NOT_FOUND;

    for (int i = size - 1; i >= 0; i--)
    {
        CSV_DATA *data = getElementArray(getElementArray(csvDatabase, i), 0);
        if (data->rowNo == val)
        {
            ne.found = FOUND;
            ne.val = i;
            break;
        }
        else if (data->rowNo < val)
        {
            ne.val = i;
            break;
        }
    }

    return ne;
}

void insertOrReplace(ARRAY *arr, CSV_DATA *data)
{
    size_t rowsize = getArraySize(arr);
    CSV_DATA *cdt = getElementArray(arr, rowsize - 1);

    if (cdt->colNo < data->colNo)
    {

        appendArray(arr, data);
        return;
    }

    for (size_t i = 0; i < rowsize; i++)
    {
        cdt = getElementArray(arr, i);

        if (cdt->colNo == data->colNo)
        {

            setElementArray(arr, i, data);
            return;
        }

        if (cdt->colNo > data->colNo)
        {

            insertArray(arr, i, data);
            return;
        }
    }
}

void insertOrAppend(CSV_DATA *data, size_t neval)
{
    ARRAY *arr = createArray(1);
    appendArray(arr, data);
    size_t csvsize = getArraySize(csvDatabase);

    CSV_DATA *last = getElementArray(getElementArray(csvDatabase, csvsize - 1), 0);

    if (last->rowNo < data->rowNo)
    {
        appendArray(csvDatabase, arr);
    }
    else
    {
        insertArray(csvDatabase, neval, arr);
    }
}

void checkValidCSVDataRange(CSV_DATA *data)
{
    if (data->colNo <= 0 || data->rowNo <= 0)
    {
        fprintf(stderr, "Invalid csv data range. r%u:c%u\n", data->rowNo, data->colNo);
        exit(1);
    }
}

void addDataToCSV(CSV_DATA *data)
{
    checkValidCSVDataRange(data);

    NearOrExact ne = linearSearchNearestRow(data->rowNo);

    if (ne.found == FOUND)
    {

        insertOrReplace(getElementArray(csvDatabase, ne.val), data);
    }
    else if (ne.found == NOT_FOUND)
    {

        insertOrAppend(data, ne.val);
    }
    else
    {
        fprintf(stderr, "Should be found or not found\n");
        exit(1);
    }
}

CSV_DATA *getEntryFromDatabase(RC rc)
{
    if (rc.colNo <= 0 || rc.rowNo <= 0)
    {
        fprintf(stderr, "Row or column <0 not allowed\n");
        return NULL;
    }

    unsigned int size = getArraySize(csvDatabase);

    int foundRow = 0;

    unsigned int foundRowIndex;

    unsigned int low = 0;
    unsigned int high = size - 1;
    unsigned int mid;
    CSV_DATA *data;

    while (low <= high)
    {

        mid = low + (high - low) / 2;

        data = getElementArray(getElementArray(csvDatabase, mid), 0);

        if (data->rowNo == rc.rowNo)
        {

            foundRow = 1;
            foundRowIndex = mid;
            break;
        }
        else if (data->rowNo < rc.rowNo)
        {
            low = mid + 1;
        }
        else
        {
            if (high == 0)
            {
                return NULL;
            }
            high = mid - 1;
        }
    }

    if (!foundRow)
    {
        return NULL;
    }

    ARRAY *row = getElementArray(csvDatabase, foundRowIndex);

    size = getArraySize(row);

    low = 0;
    high = size - 1;

    while (low <= high)
    {
        mid = low + (high - low) / 2;

        data = getElementArray(row, mid);

        if (data->colNo == rc.colNo)
        {
            return data;
        }
        else if (data->colNo < rc.colNo)
        {

            low = mid + 1;
        }
        else
        {
            if (high == 0)
            {
                return NULL;
            }
            high = mid - 1;
        }
    }
    return NULL;
}

void repeatPrintStr(char *str, unsigned int count)
{
    for (unsigned int i = 0; i < count; i++)
    {
        appendFile(str);
    }
}

int hasDecimal(float num)
{
    return (num - (int)num) != 0.0;
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
            // displayCSVDATA(data);

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
                if (hasDecimal(data->value.f))
                {
                    appendFile("%.1f", data->value.f);
                }
                else
                {
                    appendFile("%d", (int)data->value.f);
                }
            }
        }
    }
}

void processOutput()
{
    displayDatabase();
}
