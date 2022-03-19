#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

typedef struct array_list
{
    char *arrayType;
    size_t arraySize;
    void *address;
    size_t arrayLen;
} Array_list;

char parseSizeBasedOnType(char *arrayType)
{
    if (strcmp(arrayType, "int") == 0)
    {
        return 4;
    }

    if (strcmp(arrayType, "long") == 0)
    {
        return 8;
    }

    if (strcmp(arrayType, "char") == 0)
    {
        return 1;
    }
    return 0;
}

void resizeArray(Array_list **arr)
{
    void *new_cu_array = (void *)calloc((*arr)->arraySize + 6, parseSizeBasedOnType((*arr)->arrayType));

    if (strcmp((*arr)->arrayType, "int") == 0)
    {
        for (size_t i = 0; i < (*arr)->arrayLen; i++)
        {
            // *((int *)new_cu_array + i) = *((int *)(*arr)->address + i);
            ((int *)new_cu_array)[i] = ((int *)(*arr)->address)[i];
        }
    }

    if (strcmp((*arr)->arrayType, "long") == 0)
    {
        for (size_t i = 0; i < (*arr)->arrayLen; i++)
        {
            // *((int *)new_cu_array + i) = *((int *)(*arr)->address + i);
            ((unsigned long long *)new_cu_array)[i] = ((unsigned long long *)(*arr)->address)[i];
        }
    }

    if (strcmp((*arr)->arrayType, "char") == 0)
    {
        for (size_t i = 0; i < (*arr)->arrayLen; i++)
        {
            // *((int *)new_cu_array + i) = *((int *)(*arr)->address + i);
            ((char *)new_cu_array)[i] = ((char *)(*arr)->address)[i];
        }
    }

    free((*arr)->address);
    (*arr)->address = new_cu_array;
}

Array_list *createArray(char *arrayType, int arraySize)
{
    char sizeBasedOnType = parseSizeBasedOnType(arrayType);
    if (sizeBasedOnType == 0)
    {
        return NULL;
    }
    Array_list *myArray = (Array_list *)malloc(sizeof(Array_list));
    void *array = (void *)calloc(arraySize, sizeBasedOnType);
    myArray->address = array;
    myArray->arrayType = arrayType;
    myArray->arraySize = arraySize;
    myArray->arrayLen = 0;
    return myArray;
}

void push(Array_list *arr, void *data)
{

    if (arr->arrayLen == arr->arraySize)
    {
        // return a bigger array
        // create new Cu_array with bigger size and copy all data to it
        resizeArray(&arr);
        arr->arraySize = arr->arraySize + 6;
    }

    if (strcmp(arr->arrayType, "int") == 0)
    {
        *((int *)arr->address + arr->arrayLen) = *(int *)data;
    }
    if (strcmp(arr->arrayType, "long") == 0)
    {
        *((unsigned long long *)arr->address + arr->arrayLen) = *(unsigned long long *)data;
    }
    if (strcmp(arr->arrayType, "char") == 0)
    {
        *((char *)arr->address + arr->arrayLen) = *(char *)data;
    }
    arr->arrayLen = arr->arrayLen + 1;
}

void printArray(Array_list *arr)
{
    if (strcmp(arr->arrayType, "int") == 0)
    {
        for (size_t i = 0; i < arr->arrayLen; i++)
        {
            printf("%d\n", ((int *)arr->address)[i]);
        }
        return;
    }

    if (strcmp(arr->arrayType, "long") == 0)
    {
        for (size_t i = 0; i < arr->arrayLen; i++)
        {
            printf("%llu\n", ((unsigned long long *)arr->address)[i]);
        }
        return;
    }

    if (strcmp(arr->arrayType, "char") == 0)
    {
        for (size_t i = 0; i < arr->arrayLen; i++)
        {
            printf("%c\n", ((char *)arr->address)[i]);
        }
        return;
    }
}

void pop(Array_list *arr)
{
    if (arr->arrayLen == 0)
    {
        return;
    }

    arr->arrayLen--;

    if ((float)arr->arraySize / (float)arr->arrayLen >= 5.0)
    {
        printf("old size : %zu\n", arr->arraySize);
        arr->arraySize = (size_t)ceil((float)((arr->arraySize) / 2.0));
        printf("new size : %zu\n", arr->arraySize);
    }
}

// size_t find(Array_list *arr, size_t value)
// {

// }

int main()
{
    Array_list *myArr = createArray("char", 5);

    char val = 'A';
    push(myArr, &val);
    printArray(myArr);
    // free(myArr);
}

// Supported types (int long char)

// Unfinished
// support char*
// implement shift (remove head)
// implement unshift (add to head)