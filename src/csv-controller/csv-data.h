
#ifndef CSV_DATA_H
void initializeCSVDatabase();

void addNumValue(float val, unsigned int row, unsigned int col);

void addStrValue(char *val, unsigned int row, unsigned int col);

void processOutput();
void createCSVDatabase();
typedef union csv_value
{
    char *s;
    float f;
} CSV_VALUE;

enum valueType
{
    NUM_TYPE,
    STR_TYPE,
};

typedef struct csvData
{
    int valueType;
    CSV_VALUE value;
    unsigned int rowNo;
    unsigned int colNo;

} CSV_DATA;

#endif