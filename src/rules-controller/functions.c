#include "../common-headers.h"
#include "functions.h"
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
    checkValidPlaneCells(tl, br);
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

void planeOperation()
{
    float result;
    switch (currentPlaneOp)
    {
    case SUM_OP:
        result = sumOperation(tl, br);
        break;

    default:
        fprintf(stderr, "Plane Operation not defined\n");
        exit(1);
        break;
    }

    storeNumResultInDatabase(result);
}
