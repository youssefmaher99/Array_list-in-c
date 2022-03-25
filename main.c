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
    char typeSize;
} Array_list;

char parseSizeBasedOnType(char *arrayType)
{
    if (strcmp(arrayType, "int") == 0)
    {
        return sizeof(int);
    }

    if (strcmp(arrayType, "long") == 0)
    {
        return sizeof(unsigned long long);
    }

    if (strcmp(arrayType, "char") == 0)
    {
        return sizeof(char);
    }

    if (strcmp(arrayType, "char*") == 0)
    {
        return sizeof(char *);
    }

    return 0;
}

void resizeArray(Array_list *arr)
{
    void *new_cu_array = (void *)malloc(arr->typeSize * (arr->arraySize * 2));
    memcpy(new_cu_array, arr, arr->arrayLen * arr->typeSize);
    free(arr->address);
    arr->address = new_cu_array;
    arr->arraySize = arr->arraySize * 2;
}

Array_list *createArray(char *arrayType, int arraySize)
{
    char sizeBasedOnType = parseSizeBasedOnType(arrayType);
    if (sizeBasedOnType == 0)
    {
        return NULL;
    }
    Array_list *myArray = (Array_list *)malloc(sizeof(Array_list));
    myArray->address = (void *)malloc(arraySize * sizeBasedOnType);
    myArray->arrayType = arrayType;
    myArray->arraySize = arraySize;
    myArray->typeSize = sizeBasedOnType;
    myArray->arrayLen = 0;
    return myArray;
}

void push(Array_list *arr, void *data)
{

    if (arr->arrayLen == arr->arraySize)
    {
        // return a bigger array
        // create new Array_list with bigger size and copy all data to it
        resizeArray(arr);
        arr->arraySize = arr->arraySize * 2;
    }

    void *slot = arr->address + arr->arrayLen * arr->typeSize;
    memcpy(slot, data, arr->typeSize);
    arr->arrayLen = arr->arrayLen + 1;
}

void printArray(Array_list *arr)
{

    if (arr->arrayLen == 0)
    {
        printf("{}\n");
        return;
    }

    if (strcmp(arr->arrayType, "int") == 0)
    {

        for (size_t i = 0; i < arr->arrayLen; i++)
        {
            printf("%d\n", ((int *)arr->address)[i]);
        }
    }

    else if (strcmp(arr->arrayType, "long") == 0)
    {

        for (size_t i = 0; i < arr->arrayLen; i++)
        {
            printf("%llu\n", ((unsigned long long *)arr->address)[i]);
        }
    }

    else if (strcmp(arr->arrayType, "char") == 0)
    {

        for (size_t i = 0; i < arr->arrayLen; i++)
        {
            printf("%c\n", ((char *)arr->address)[i]);
        }
    }

    else if (strcmp(arr->arrayType, "char*") == 0)
    {

        for (size_t i = 0; i < arr->arrayLen; i++)
        {
            printf("%s\n", ((char **)arr->address)[i]);
        }
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

ptrdiff_t getIndexOf(Array_list *arr, void *val)
{

    if (strcmp(arr->arrayType, "char*") == 0)
    {
        for (int i = 0; i < arr->arrayLen; i++)
        {
            if (strcmp(((char **)arr->address)[i], val) == 0)
            {
                return i;
            }
        }
        return -1;
    }
    else
    {
        void *ptr = arr->address;
        for (int i = 0; i < arr->arrayLen; i++)
        {
            if (memcmp(ptr, val, arr->typeSize) == 0)
            {
                return i;
            }
            ptr = ptr + arr->typeSize;
        }
    }
    return -1;
}

void *getElementByIndex(Array_list *arr, size_t index)
{
    return arr->address + (arr->typeSize * index);
}

void clear(Array_list *arr)
{
    if (arr->arrayLen == 0)
    {
        return;
    }

    free(arr->address);
    size_t proposedNewSize = (size_t)ceil((float)arr->arrayLen / 2);
    // at least 10 elements minimum
    if (proposedNewSize < 10)
    {
        proposedNewSize = 10;
    }
    arr->arraySize = proposedNewSize;
    arr->arrayLen = 0;
}

int main()
{
    Array_list *myArr = createArray("char*", 5);
    char *val = "hello world";

    push(myArr, &val);
    val = "test test";

    push(myArr, &val);
    val = "abc efg h";

    push(myArr, &val);
    printArray(myArr);
}