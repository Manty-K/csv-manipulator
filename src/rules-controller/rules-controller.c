#include "../common-headers.h"

#include "rules-controller.h"
#include "../csv-controller/csv-data.h"

RC currentRC;

void setRC(unsigned int rowNo, unsigned int colNo)
{

    currentRC.rowNo = rowNo;
    currentRC.colNo = colNo;
}

void assignString(char *str)
{
    CSV_DATA *data = malloc(sizeof(CSV_DATA));
    data->rowNo = currentRC.rowNo;
    data->colNo = currentRC.colNo;
    data->value.s = str;
    data->valueType = STR_TYPE;

    addDataToCSV(data);
}