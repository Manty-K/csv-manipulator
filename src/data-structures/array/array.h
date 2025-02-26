#ifndef ARRAY_H
typedef struct
{

    void **ptr;
    size_t cap;
    size_t filled;

} ARRAY;

ARRAY *createArray(size_t);

void appendArray(ARRAY *, void *);

void *getElementArray(ARRAY *, size_t);

void setElementArray(ARRAY *, size_t, void *);

void *popElementArray(ARRAY *);
void insertArray(ARRAY *array, size_t index, void *data);

char isEmptyArray(ARRAY *array);
size_t getArraySize(ARRAY *array);
void freeArray(ARRAY *);

#endif
