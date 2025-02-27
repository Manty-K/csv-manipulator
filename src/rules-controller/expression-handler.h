

#ifndef EXPRESSION_HANDLER_H
#include "../csv-controller/csv-data.h"

typedef union expdataval
{
    char *s;
    float f;
    RC rc;
} EXP_DATA_VAL;

enum exp_data_type
{
    OP,
    NUM,
    CSV_ELE,
};

typedef struct exp_data
{
    enum exp_data_type type;
    EXP_DATA_VAL val;
} EXP_DATA;

void expressionStart();
void expressionEnd();
void setIndentifier();
void pushRC();
void pushNum(float num);
void pushOperator(char *op);
#endif