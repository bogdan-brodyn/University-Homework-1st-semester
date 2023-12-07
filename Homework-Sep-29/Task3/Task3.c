#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define TEST_ARRAY_SIZE 100000

typedef enum
{
    defaultErrorCode,
    memoryLack,
    countingSortLimitExceeded,
    testFailed
} ErrorCode;

void swapArrayElements(int* array, size_t index1, size_t index2)
{
    int temp = array[index1];
    array[index1] = array[index2];
    array[index2] = temp;
}

void bubbleSort(int* array, size_t arraySize)
{
    for (size_t i = 0; i < arraySize; ++i)
    {
        for (size_t j = i + 1; j < arraySize; ++j)
        {
            if (array[i] >= array[j])
            {
                swapArrayElements(array, i, j);
            }
        }
    }
}

ErrorCode countingSort(int* array, size_t arraySize)
{
    int* arrayElementsCount = (int*)calloc(arraySize, sizeof(int));
    if (arrayElementsCount == NULL)
    {
        return memoryLack;
    }
    for (size_t i = 0; i < arraySize; ++i)
    {
        arrayElementsCount[i] = 0;
    }

    for (size_t i = 0; i < arraySize; ++i)
    {
        if (array[i] >= arraySize)
        {
            free(arrayElementsCount);
            return countingSortLimitExceeded;
        }
        ++arrayElementsCount[array[i]];
    }

    size_t fillingStart = 0;
    for (size_t element = 0; element < arraySize; ++element)
    {
        for (size_t filledElementsCount = 0; filledElementsCount < arrayElementsCount[element]; ++filledElementsCount)
        {
            array[fillingStart + filledElementsCount] = element;
        }
        fillingStart += arrayElementsCount[element];
    }

    free(arrayElementsCount);
    return defaultErrorCode;
}

ErrorCode getTwoTestArraysSpace(int** testArray1, int** testArray2, size_t testArraySize)
{
    *testArray1 = (int*)malloc(sizeof(int) * testArraySize);
    *testArray2 = (int*)malloc(sizeof(int) * testArraySize);
    if (*testArray1 == NULL || *testArray2 == NULL)
    {
        free(*testArray1);
        free(*testArray2);
        *testArray1 = NULL;
        *testArray2 = NULL;
        return memoryLack;
    }
    srand(time(NULL));
    for (int i = 0; i < testArraySize; ++i)
    {
        testArray1[i] = testArray2[i] = rand() % testArraySize;
    }
    return defaultErrorCode;
}

bool testSortsWorkTheSame(void)
{
    const int arraySize = 1000;
    int* arrayForBubbleSort = NULL;
    int* arrayForCountSort = NULL;
    if (getTwoTestArraysSpace(&arrayForBubbleSort, &arrayForCountSort, arraySize) != defaultErrorCode)
    {
        return false;
    }

    bool testResult = true;
    bubbleSort(arrayForBubbleSort, arraySize);
    int errorCode = countingSort(arrayForCountSort, arraySize);
    if (errorCode != 0)
    {
        testResult = false;
    }
    else
    {
        for (int i = 0; i < arraySize; ++i)
        {
            if (!((i == arraySize - 1 || arrayForBubbleSort[i] <= arrayForBubbleSort[i + 1]) 
                && arrayForBubbleSort[i] == arrayForCountSort[i]))
            {
                testResult = false;
            }
        }
    }
    free(arrayForBubbleSort);
    free(arrayForCountSort);
    return testResult;
}

int main(void)
{
    if (!testSortsWorkTheSame())
    {
        printf("Sorry, program is working incorrectly\n");
        return testFailed;
    }
    printf("Program is working correctly\n");
    
    int* testArray1 = NULL;
    int* testArray2 = NULL;
    if (getTwoTestArraysSpace(&testArray1, &testArray2, TEST_ARRAY_SIZE) != defaultErrorCode)
    {
        printf("Sorry, program didn't have enough memory to run\n");
        return memoryLack;
    }

    printf("Sorting an array of length %d took:\n", TEST_ARRAY_SIZE);
    clock_t begin = clock();
    bubbleSort(testArray1, TEST_ARRAY_SIZE);
    clock_t end = clock();
    printf("Bubble sort took %d clocks\n", end - begin);

    begin = clock();
    int errorCode = countingSort(testArray2, TEST_ARRAY_SIZE);
    end = clock();
    if (errorCode != 0)
    {
        printf("Counting sort failed\n");
        free(testArray1);
        free(testArray2);
        return countingSortLimitExceeded;
    }
    printf("Counting sort took %d clocks\n", end - begin);

    free(testArray1);
    free(testArray2);
}
