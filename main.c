#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct array_list
{
    char *arrayType;
    size_t arraySize;
    void *address;
    size_t arrayLen;
} Array_list;

short parseSizeBasedOnType(char *arrayType)
{
    if (strcmp(arrayType, "int") == 0)
    {
        return 4;
    }
    printf("eh dah?\n");
}

Array_list *createArray(char *arrayType, int arraySize)
{
    Array_list *myArray = (Array_list *)malloc(sizeof(Array_list));
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

void push(Array_list **arr, void *data)
{

    if ((*arr)->arrayLen == (*arr)->arraySize)
    {
        // return a bigger array
        // create new Array_list with bigger size and copy all data to it
        void *new_cu_array = (void *)calloc((*arr)->arraySize + 2, parseSizeBasedOnType((*arr)->arrayType));
        for (int i = 0; i < (*arr)->arrayLen; i++)
        {
            ((int *)new_cu_array)[i] = ((int *)(*arr)->address)[i];
        }

        free((*arr)->address);
        (*arr)->address = new_cu_array;
        (*arr)->arraySize = (*arr)->arraySize + 2;
    }

    if (strcmp((*arr)->arrayType, "int") == 0)
    {
        *((int *)(*arr)->address + (*arr)->arrayLen) = *(int *)data;
    }
    (*arr)->arrayLen = (*arr)->arrayLen + 1;
}

void printArray(Array_list *arr)
{
    for (int i = 0; i < arr->arrayLen; i++)
    {
        printf("%d ", ((int *)arr->address)[i]);
    }
    printf("\n");
}

void exchange(int **ptr)
{
    int *new_ptr = (void *)calloc(1, sizeof(int));
    *new_ptr = 55;
    *ptr = new_ptr;
}

int main()
{
    Array_list *myArr = createArray("int", 5);

    int val = 1;
    push(&myArr, &val);

    val = 2;
    push(&myArr, &val);

    val = 3;
    push(&myArr, &val);

    val = 4;
    push(&myArr, &val);

    val = 5;
    push(&myArr, &val);
    val = 6;
    push(&myArr, &val);
    val = 7;
    push(&myArr, &val);
    printArray(myArr);
}
// implement pop

// define table fields -name - type
// define start adding to the table