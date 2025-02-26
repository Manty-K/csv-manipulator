#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    void **ptr;
    size_t cap;
    size_t filled;
} ARRAY;

ARRAY *createArray(size_t capacity)
{
    if (capacity == 0)
    {
        fprintf(stderr, "Invalid capacity: %zu\n", capacity);
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
        size_t newCap = array->cap * 2;
        if (newCap < array->cap) // Overflow check
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

void *getElementArray(ARRAY *array, size_t index)
{
    if (array == NULL || index >= array->filled)
    {
        fprintf(stderr, "get : Index %zu out of bounds. Filled: %zu, Cap: %zu\n",
                index, array ? array->filled : 0, array ? array->cap : 0);
        return NULL;
    }
    return array->ptr[index];
}

void setElementArray(ARRAY *array, size_t index, void *data)
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

void insertArray(ARRAY *array, size_t index, void *data)
{
    if (array == NULL || index > array->filled)
    {
        fprintf(stderr, "Index %zu out of bounds for insertion.\n", index);
        return;
    }

    if (array->filled == array->cap)
    {
        size_t newCap = array->cap * 2;
        if (newCap < array->cap) // Overflow check
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

    // Shift elements to the right
    for (size_t i = array->filled; i > index; i--)
    {
        array->ptr[i] = array->ptr[i - 1];
    }

    array->ptr[index] = data;
    array->filled++;
}

size_t getArraySize(ARRAY *arr)
{
    return arr ? arr->filled : 0;
}

void freeArray(ARRAY *array, void (*free_func)(void *))
{
    if (array == NULL)
        return;
    if (free_func != NULL)
    {
        for (size_t i = 0; i < array->filled; i++)
        {
            free_func(array->ptr[i]);
        }
    }
    free(array->ptr);
    free(array);
}
