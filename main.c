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

    if (strcmp(arrayType, "char*") == 0)
    {
        return 8;
    }

    return 0;
}

void resizeArray(Array_list **arr)
{
    void *new_cu_array = (void *)calloc((*arr)->arraySize * 2, parseSizeBasedOnType((*arr)->arrayType));

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

    if (strcmp((*arr)->arrayType, "char*") == 0)
    {
        for (size_t i = 0; i < (*arr)->arrayLen; i++)
        {
            // *((int *)new_cu_array + i) = *((int *)(*arr)->address + i);
            ((char **)new_cu_array)[i] = ((char **)(*arr)->address)[i];
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
        // create new Array_list with bigger size and copy all data to it
        resizeArray(&arr);
        arr->arraySize = arr->arraySize * 2;
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
    if (strcmp(arr->arrayType, "char*") == 0)
    {
        *((char **)arr->address + arr->arrayLen) = *(char **)data;
    }
    arr->arrayLen = arr->arrayLen + 1;
}

void printArray(Array_list *arr)
{
    if (strcmp(arr->arrayType, "int") == 0)
    {
        if (arr->arrayLen == 0)
        {
            printf("{}\n");
            return;
        }
        for (size_t i = 0; i < arr->arrayLen; i++)
        {
            printf("%d\n", ((int *)arr->address)[i]);
        }
        return;
    }

    if (strcmp(arr->arrayType, "long") == 0)
    {
        if (arr->arrayLen == 0)
        {
            printf("{}\n");
            return;
        }
        for (size_t i = 0; i < arr->arrayLen; i++)
        {
            printf("%llu\n", ((unsigned long long *)arr->address)[i]);
        }
        return;
    }

    if (strcmp(arr->arrayType, "char") == 0)
    {
        if (arr->arrayLen == 0)
        {
            printf("{}\n");
            return;
        }
        for (size_t i = 0; i < arr->arrayLen; i++)
        {
            printf("%c\n", ((char *)arr->address)[i]);
        }
        return;
    }

    if (strcmp(arr->arrayType, "char*") == 0)
    {
        if (arr->arrayLen == 0)
        {
            printf("{}\n");
            return;
        }
        for (size_t i = 0; i < arr->arrayLen; i++)
        {
            printf("%s\n", ((char **)arr->address)[i]);
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

ptrdiff_t getIndexOf(Array_list *arr, size_t val)
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
    if (strcmp(arr->arrayType, "long") == 0)
    {
        for (int i = 0; i < arr->arrayLen; i++)
        {
            if (((unsigned long long *)arr->address)[i] == val)
            {
                return i;
            }
        }
        return -1;
    }
    if (strcmp(arr->arrayType, "int") == 0)
    {
        for (int i = 0; i < arr->arrayLen; i++)
        {
            if (((int *)arr->address)[i] == val)
            {
                return i;
            }
        }
        return -1;
    }
    if (strcmp(arr->arrayType, "char") == 0)
    {
        for (int i = 0; i < arr->arrayLen; i++)
        {
            if (strcmp(((char *)arr->address)[i], val) == 0)
            {
                return i;
            }
        }
        return -1;
    }
    return -1;
}

ptrdiff_t getElementByIndex(Array_list *arr, ptrdiff_t index)
{
    if (index == -1)
    {
        fprintf(stderr, "Invalid index\n");
        exit(1);
    }

    if (strcmp(arr->arrayType, "char*") == 0)
    {
        if (arr->arraySize <= index)
        {
            fprintf(stderr, "Index out of range\n");
            exit(1);
        }
        return ((char **)arr->address)[index];
    }
    if (strcmp(arr->arrayType, "long") == 0)
    {
        if (arr->arraySize <= index)
        {
            fprintf(stderr, "Index out of range\n");
            exit(1);
        }
        return ((unsigned long long *)arr->address)[index];
    }
    if (strcmp(arr->arrayType, "int") == 0)
    {
        if (arr->arraySize <= index)
        {
            fprintf(stderr, "Index out of range\n");
            exit(1);
        }
        return ((int *)arr->address)[index];
    }
    if (strcmp(arr->arrayType, "char") == 0)
    {
        if (arr->arraySize <= index)
        {
            fprintf(stderr, "Index out of range\n");
            exit(1);
        }
        return ((char *)arr->address)[index];
    }
    fprintf(stderr, "Invalid ArrayList type\n");
    exit(1);
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