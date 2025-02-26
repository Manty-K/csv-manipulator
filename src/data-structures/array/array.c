#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    void **ptr;
    int cap;
    int filled;
} ARRAY;

ARRAY *createArray(int capacity)
{
    if (capacity <= 0)
    {
        fprintf(stderr, "Invalid capacity: %d\n", capacity);
        return NULL;
    }
    ARRAY *arr = malloc(sizeof(ARRAY));
    if (arr == NULL)
    {
        perror("malloc failed");
        return NULL;
    }
    arr->cap = capacity;
    arr->filled = 0;
    arr->ptr = malloc(sizeof(void *) * arr->cap);
    if (arr->ptr == NULL)
    {
        perror("malloc failed");
        free(arr);
        return NULL;
    }
    return arr;
}
char isEmptyArray(ARRAY *array)
{
    return array == NULL || array->filled == 0;
}

void appendArray(ARRAY *array, void *data)
{
    if (array == NULL)
        return;

    if (array->filled == array->cap)
    {
        int newCap = array->cap * 2;
        if (newCap < array->cap)
        {
            fprintf(stderr, "Array capacity overflow.\n");
            return;
        }
        void **newPtr = realloc(array->ptr, sizeof(void *) * newCap);
        if (newPtr == NULL)
        {
            fprintf(stderr, "realloc failed!\n");
            return;
        }
        array->ptr = newPtr;
        array->cap = newCap;
    }
    array->ptr[array->filled++] = data;
}

void *getElementArray(ARRAY *array, int index)
{
    if (array == NULL || index >= array->filled || index < 0)
    {
        fprintf(stderr, "Index %d out of bounds. Filled: %d, Cap: %d\n",
                index, array ? array->filled : -1, array ? array->cap : -1);
        return NULL;
    }
    return array->ptr[index];
}

void setElementArray(ARRAY *array, int index, void *data)
{
    if (array == NULL || index >= array->filled)
    {
        fprintf(stderr, "Cannot set out of capacity\n");
        return;
    }

    array->ptr[index] = data;
}

void *popElementArray(ARRAY *array)
{
    if (array == NULL || isEmptyArray(array))
    {
        fprintf(stderr, "Array empty cannot pop.\n");
        return NULL;
    }
    return array->ptr[--array->filled];
}

int getArraySize(ARRAY *arr)
{
    return arr->filled;
}

void freeArray(ARRAY *array, void (*free_func)(void *))
{
    if (array == NULL)
        return;
    if (free_func != NULL)
    {
        for (int i = 0; i < array->filled; i++)
        {
            free_func(array->ptr[i]);
        }
    }
    free(array->ptr);
    free(array);
}
