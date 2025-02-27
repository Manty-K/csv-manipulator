#include "../common-headers.h"
#include "functions.h"
#include <float.h>
extern RC currentRC;
enum plane_op currentPlaneOp;

RC tl;
RC br;

void setTl()
{
    tl = currentRC;
}
void setBr()
{
    br = currentRC;
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
