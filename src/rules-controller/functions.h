#ifndef FUNCTIONS_H
#include "expression-handler.h"
enum plane_op
{
    SUM_OP,
    AVG_OP,
    MIN_OP,
    MAX_OP,
};
typedef enum direction
{
    VERTICAL,
    HORIZONTAL,
} DIRECTION;

void planeOperation();
void sortOperation();
void setPlaneOp(enum plane_op op);
void setTl();
void setBr();
void setCurrentDirection(DIRECTION direction);

#endif