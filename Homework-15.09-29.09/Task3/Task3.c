#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

void swapArrayElements(int* array, int index1, int index2)
{
    int temp = array[index1];
    array[index1] = array[index2];
    array[index2] = temp;
}

void bubbleSort(int* array, int arraySize)
{
    for (int i = 0; i < arraySize; ++i)
    {
        for (int j = i + 1; j < arraySize; ++j)
        {
            if (array[i] >= array[j])
            {
                swapArrayElements(array, i, j);
            }
        }
    }
}

int countingSort(int* array, int arraySize)
{
    int* arrayElementsCount = (int*)malloc(sizeof(int) * arraySize);
    for (int i = 0; i < arraySize; ++i)
    {
        arrayElementsCount[i] = 0;
    }

    for (int i = 0; i < arraySize; ++i)
    {
        if (array[i] >= arraySize)
        {
            free(arrayElementsCount);
            return 1;
        }
        ++arrayElementsCount[array[i]];
    }

    int fillingStart = 0;
    for (int element = 0; element < arraySize; ++element)
    {
        for (int filledElementsCount = 0; filledElementsCount < arrayElementsCount[element]; ++filledElementsCount)
        {
            array[fillingStart + filledElementsCount] = element;
        }
        fillingStart += arrayElementsCount[element];
    }

    free(arrayElementsCount);
}

bool testSortsWorkTheSame(void)
{
    int arraySize = 1000;
    int* array1 = (int*)malloc(sizeof(int) * arraySize);
    int* array2 = (int*)malloc(sizeof(int) * arraySize);
    for (int i = 0; i < arraySize; ++i)
    {
        array1[i] = array2[i] = rand() % arraySize;
    }

    bubbleSort(array1, arraySize);
    int errorCode = countingSort(array2, arraySize);
    if (errorCode != 0)
    {
        free(array1);
        free(array2);
        return false;
    }
    for (int i = 0; i < arraySize; ++i)
    {
        if (!((i == arraySize - 1 || array1[i] <= array1[i + 1]) && array1[i] == array2[i]))
        {
            free(array1);
            free(array2);
            return false;
        }
    }

    free(array1);
    free(array2);
    return true;
}

int main(void)
{
    if (!testSortsWorkTheSame())
    {
        printf("Sorry, program is working incorrectly\n");
        return 1;
    }
    printf("Program is working correctly\n");

    int testArraySize = 100000;
    int* testArray1 = (int*)malloc(sizeof(int) * testArraySize);
    int* testArray2 = (int*)malloc(sizeof(int) * testArraySize);
    if (testArray1 == NULL || testArray2 == NULL)
    {
        printf("Sorry, program didn't have enough memory to run\n");
        free(testArray1);
        free(testArray2);
        return 2;
    }
    for (int i = 0; i < testArraySize; ++i)
    {
        testArray1[i] = testArray2[i] = rand() % testArraySize;
    }

    printf("Sorting an array of length %d took:\n", testArraySize);
    clock_t begin = clock();
    bubbleSort(testArray1, testArraySize);
    clock_t end = clock();
    printf("Bubble sort %d clocks\n", end - begin);

    begin = clock();
    int errorCode = countingSort(testArray2, testArraySize);
    end = clock();
    if (errorCode != 0)
    {
        printf("Counting sort failed\n");
        free(testArray1);
        free(testArray2);
        return 3;
    }
    printf("Counting sort %d clocks\n", end - begin);

    free(testArray1);
    free(testArray2);
}