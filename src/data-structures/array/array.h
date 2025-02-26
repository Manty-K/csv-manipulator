#ifndef ARRAY_H
typedef struct
{

    void **ptr;
    int cap;
    int filled;

} ARRAY;

ARRAY *createArray(int);

void appendArray(ARRAY *, void *);

void *getElementArray(ARRAY *, int);

void setElementArray(ARRAY *, int, void *);

void *popElementArray(ARRAY *);
void insertArray(ARRAY *array, int index, void *data);

char isEmptyArray(ARRAY *array);
int getArraySize(ARRAY *array);
void freeArray(ARRAY *);

#endif
