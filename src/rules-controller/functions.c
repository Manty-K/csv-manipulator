#include "../common-headers.h"
#include "functions.h"
#include <float.h>
#include "../data-structures/array/array.h"
extern RC currentRC;
enum plane_op currentPlaneOp;
extern RC identifier;
RC tl;
RC br;

DIRECTION currentDirection;

void setTl()
{
    tl = currentRC;
}
void setBr()
{
    br = currentRC;
}

void setCurrentDirection(DIRECTION direction)
{
    currentDirection = direction;
}

void setPlaneOp(enum plane_op op)
{

    currentPlaneOp = op;
}

void checkValidPlaneCells()
{
    if (tl.rowNo > br.rowNo || tl.colNo > br.colNo)
    {
        fprintf(stderr, "Invalid Plane r%uc%u -> r%uc%u\n", tl.rowNo, tl.colNo, br.rowNo, br.colNo);
        exit(1);
    }
}

float sumOperation()
{
    checkValidPlaneCells();
    RC rc;
    CSV_DATA *data;

    float result = 0;

    for (unsigned int col = tl.colNo; col <= br.colNo; col++)
    {

        for (unsigned int row = tl.rowNo; row <= br.rowNo; row++)
        {
            rc.rowNo = row;
            rc.colNo = col;
            data = getEntryFromDatabase(rc);
            if (data == NULL)
            {
                continue;
            }
            if (data->valueType == NUM_TYPE)
            {
                result += data->value.f;
            }
        }
    }
    return result;
}

float avgOperation()
{
    checkValidPlaneCells();
    RC rc;
    CSV_DATA *data;

    float result = 0;
    unsigned int count = 0;

    for (unsigned int col = tl.colNo; col <= br.colNo; col++)
    {
        for (unsigned int row = tl.rowNo; row <= br.rowNo; row++)
        {
            rc.rowNo = row;
            rc.colNo = col;
            data = getEntryFromDatabase(rc);
            if (data == NULL)
            {
                continue;
            }
            if (data->valueType == NUM_TYPE)
            {
                result += data->value.f;
                count++;
            }
        }
    }
    return result / count;
}

float minOperation()
{
    checkValidPlaneCells();
    RC rc;
    CSV_DATA *data;

    float result = FLT_MAX;

    for (unsigned int col = tl.colNo; col <= br.colNo; col++)
    {
        for (unsigned int row = tl.rowNo; row <= br.rowNo; row++)
        {
            rc.rowNo = row;
            rc.colNo = col;
            data = getEntryFromDatabase(rc);
            if (data == NULL)
            {
                continue;
            }
            if (data->valueType == NUM_TYPE)
            {
                if (data->value.f < result)
                {
                    result = data->value.f;
                }
            }
        }
    }
    return result;
}

float maxOperation()
{
    checkValidPlaneCells();
    RC rc;
    CSV_DATA *data;

    float result = FLT_MIN;

    for (unsigned int col = tl.colNo; col <= br.colNo; col++)
    {
        for (unsigned int row = tl.rowNo; row <= br.rowNo; row++)
        {
            rc.rowNo = row;
            rc.colNo = col;
            data = getEntryFromDatabase(rc);
            if (data == NULL)
            {
                continue;
            }
            if (data->valueType == NUM_TYPE)
            {
                if (data->value.f > result)
                {
                    result = data->value.f;
                }
            }
        }
    }
    return result;
}
int cmpCSVDATA(const void *a, const void *b)
{
    float fa = **(float **)a;
    float fb = **(float **)b;
    if (fa < fb)
        return -1;
    if (fa > fb)
        return 1;
    return 0;
}

void sortArr(ARRAY *arr)
{
    qsort(arr->ptr, getArraySize(arr), sizeof(float *), cmpCSVDATA);
}

void processArr(ARRAY *arr)
{
    float fval;
    for (size_t i = 0; i < getArraySize(arr); i++)
    {
        fval = *(float *)getElementArray(arr, i);

        CSV_DATA *data = malloc(sizeof(CSV_DATA));
        data->value.f = fval;
        data->valueType = NUM_TYPE;
        if (currentDirection == VERTICAL)
        {
            data->colNo = identifier.colNo;
            data->rowNo = identifier.rowNo + i;
        }
        else
        {
            data->colNo = identifier.colNo + i;
            data->rowNo = identifier.rowNo;
        }
        addDataToCSV(data);
    }
}

void sortOperation()
{
    checkValidPlaneCells();
    RC rc;
    CSV_DATA *data;

    ARRAY *myArr = createArray(1);

    for (unsigned int col = tl.colNo; col <= br.colNo; col++)
    {
        for (unsigned int row = tl.rowNo; row <= br.rowNo; row++)
        {
            rc.rowNo = row;
            rc.colNo = col;
            data = getEntryFromDatabase(rc);
            if (data == NULL)
            {
                continue;
            }
            if (data->valueType == STR_TYPE)
            {
                fprintf(stderr, "String not allowed in Sort\n");
                exit(1);
            }
            if (data->valueType == NUM_TYPE)
            {
                float *fval = malloc(sizeof(float));

                fval = &data->value.f;

                appendArray(myArr, fval);
            }
        }
    }

    sortArr(myArr);
    processArr(myArr);
}

void planeOperation()
{
    float result;
    switch (currentPlaneOp)
    {
    case SUM_OP:
        result = sumOperation();
        break;
    case AVG_OP:
        result = avgOperation();
        break;
    case MIN_OP:
        result = minOperation();
        break;
    case MAX_OP:
        result = maxOperation();
        break;

    default:
        fprintf(stderr, "Plane Operation not defined\n");
        exit(1);
        break;
    }

    storeNumResultInDatabase(result);
}
