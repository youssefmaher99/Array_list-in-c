#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

typedef struct cu_array
{
    char *arrayType;
    size_t arraySize;
    void *address;
    size_t arrayLen;
} Cu_array;

short parseSizeBasedOnType(char *arrayType)
{
    if (strcmp(arrayType, "int") == 0)
    {
        return 4;
    }
    printf("eh dah?\n");
}

void resizeArray(Cu_array **arr)
{
    void *new_cu_array = (void *)calloc((*arr)->arraySize + 6, parseSizeBasedOnType((*arr)->arrayType));
    for (int i = 0; i < (*arr)->arrayLen; i++)
    {
        // *((int *)new_cu_array + i) = *((int *)(*arr)->address + i);
        ((int *)new_cu_array)[i] = ((int *)(*arr)->address)[i];
    }

    free((*arr)->address);
    (*arr)->address = new_cu_array;
}

Cu_array *createArray(char *arrayType, int arraySize)
{
    Cu_array *myArray = (Cu_array *)malloc(sizeof(Cu_array));
    if (strcmp(arrayType, "int") == 0)
    {
        void *array = (void *)calloc(arraySize, parseSizeBasedOnType(arrayType));
        myArray->address = array;
        myArray->arrayType = arrayType;
        myArray->arraySize = arraySize;
        myArray->arrayLen = 0;
        return myArray;
    }
}

void push(Cu_array *arr, void *data)
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
    arr->arrayLen = arr->arrayLen + 1;
}

void printArray(Cu_array *arr)
{
    for (int i = 0; i < arr->arrayLen; i++)
    {
        // printf("%d ", *((int *)arr->address + i));
        printf("%d ", ((int *)arr->address)[i]);
    }
    printf("\n");
}

void pop(Cu_array *arr)
{
    if (arr->arrayLen == 0)
    {
        return;
    }

    arr->arrayLen--;

    if ((float)arr->arraySize / (float)arr->arrayLen >= 5.0)
    {
        printf("old size : %zu\n",arr->arraySize);
        arr->arraySize = (size_t)ceil((float)((arr->arraySize)/2.0));
        printf("new size : %zu\n",arr->arraySize);
    }

}

int main()
{
    Cu_array *myArr = createArray("int", 4);

    int val = 1;
    push(myArr, &val);

    val = 2;
    push(myArr, &val);

    val = 3;
    push(myArr, &val);

    val = 4;
    push(myArr, &val);
    val = 5;
    push(myArr, &val);
    printArray(myArr);
    // free(myArr->address);
    // free(myArr);
}

// Finished
// dynamicly allocate memory of certain size
// push data to a dynamicly allocated memory with the ability to expand the memory in case of reaching the initial the max allocated memory
// implement pop (remove tail)

// Unfinished
// implement shift (remove head)
// implement unshift (add to head)