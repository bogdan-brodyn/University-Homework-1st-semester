#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "GetMostCommonNumber.h"

#define WRITTEN_TEST_COUNT 5

typedef enum
{
    testPassed,
    testFailed,
    testExecutedWithAnError
} TestResult;

TestResult randomTest(void)
{
    const size_t randomArraySize = (const size_t)1e6;
    int* const randomArray = (int* const)malloc(sizeof(int) * randomArraySize);
    int* const arrayElementsCount = (int* const)malloc(sizeof(int) * randomArraySize);
    if (randomArray == NULL || arrayElementsCount == NULL)
    {
        return testExecutedWithAnError;
    }
    for (size_t i = 0; i < randomArraySize; ++i)
    {
        arrayElementsCount[i] = 0;
    }
    for (size_t i = 0; i < randomArraySize; ++i)
    {
        randomArray[i] = rand() % randomArraySize;
        ++arrayElementsCount[randomArray[i]];
    }

    ErrorCode errorCode = defaultErrorCode;
    const int mostCommonNumber = getMostCommonNumber(randomArray, randomArraySize, &errorCode);
    if (errorCode != defaultErrorCode)
    {
        return testExecutedWithAnError;
    }
    const int mostCommonNumberCount = arrayElementsCount[mostCommonNumber];
    for (size_t i = 0; i < randomArraySize; ++i)
    {
        if (mostCommonNumberCount < arrayElementsCount[i])
        {
            return testFailed;
        }
    }
    return testPassed;
}

int testGetMostCommonNumber(void)
{
    int testArrays[WRITTEN_TEST_COUNT][7] = { {1}, {2, 2}, {1, 2, 2}, {3, 3, 2, 1}, {3, 2, 1, 2, 3, 4, 2} };
    const size_t testArraySizes[WRITTEN_TEST_COUNT] = { 1, 2, 3, 4, 7 };
    const int correctResults[WRITTEN_TEST_COUNT] = { 1, 2, 2, 3, 2 };
    for (size_t testIndex = 0; testIndex < WRITTEN_TEST_COUNT; ++testIndex)
    {
        ErrorCode errorCode = defaultErrorCode;
        if (getMostCommonNumber(testArrays[testIndex],
            testArraySizes[testIndex], &errorCode) != correctResults[testIndex]
            || errorCode != defaultErrorCode)
        {
            return (int)(testIndex + 1);
        }
    }
    return 0;
}

int main(void)
{
    srand(time(NULL));
    const int errorCode = testGetMostCommonNumber();
    if (errorCode != 0)
    {
        printf("The program gave an incorrect answer on test %d\n", errorCode);
        return errorCode;
    }
    printf("The program has passed all the written tests\n");
    if (randomTest() != testPassed)
    {
        printf("The program has failed random test\n");
        return WRITTEN_TEST_COUNT + 1;
    }
    printf("The program has passed random test\n");
    return 0;
}
