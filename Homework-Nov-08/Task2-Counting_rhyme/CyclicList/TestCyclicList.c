#include <stdio.h>
#include <stdlib.h>

#include "CyclicList.h"

typedef enum
{
    testPassed,
    testFailed,
    testMemoryLack
} TestResult;

static bool getNextAndCheckValue(CyclicList* const cyclicList, CyclicListElement** const cyclicListElement, int correctValue)
{
    int currentValue = 0;
    bool testResult =
        getNext(cyclicList, cyclicListElement) == cyclicListDefaultErrorCode
        && getCyclicListElementValue(*cyclicListElement, &currentValue) == cyclicListDefaultErrorCode
        && currentValue == correctValue;
    return testResult;
}

static TestResult test1(void)
{
    CyclicList* cyclicList = createCyclicList();
    if (cyclicList == NULL)
    {
        return testMemoryLack;
    }
    CyclicListElement* cyclicListElement = NULL;
    int value = 0;
    bool testResult =
        push(cyclicList, 1) == cyclicListDefaultErrorCode
        && push(cyclicList, 2) == cyclicListDefaultErrorCode
        && push(cyclicList, 3) == cyclicListDefaultErrorCode
        && getNextAndCheckValue(cyclicList, &cyclicListElement, 3)
        && getNextAndCheckValue(cyclicList, &cyclicListElement, 1)
        && getNextAndCheckValue(cyclicList, &cyclicListElement, 2)
        && getNextAndCheckValue(cyclicList, &cyclicListElement, 3)
        && removeNext(&cyclicList, cyclicListElement) == cyclicListDefaultErrorCode
        && getNextAndCheckValue(cyclicList, &cyclicListElement, 2)
        && getNextAndCheckValue(cyclicList, &cyclicListElement, 3)
        && removeNext(&cyclicList, cyclicListElement) == cyclicListDefaultErrorCode
        && getNextAndCheckValue(cyclicList, &cyclicListElement, 3)
        && removeNext(&cyclicList, cyclicListElement) == cyclicListDefaultErrorCode
        && isEmpty(cyclicList);
    deleteCyclicList(&cyclicList);
    return testResult && cyclicList == NULL ? testPassed : testFailed;
}

static TestResult test2(void)
{
    CyclicList* const nullCyclicList = NULL;
    CyclicList* emptyCyclicList = createCyclicList();
    CyclicListElement* const cyclicListElement = NULL;
    if (emptyCyclicList == NULL)
    {
        return testMemoryLack;
    }
    bool testResult =
        push(NULL, 1) == cyclicListNullPointer
        && removeNext(NULL, NULL) == cyclicListNullPointer
        && removeNext(&nullCyclicList, NULL) == cyclicListNullPointer
        && removeNext(&emptyCyclicList, NULL) == cyclicListNullPointer
        && getNext(NULL, &cyclicListElement) == cyclicListNullPointer
        && getNext(emptyCyclicList, NULL) == cyclicListNullPointer
        && getNext(emptyCyclicList, &cyclicListElement) == cyclicListIsEmpty
        && getCyclicListElementValue(cyclicListElement, NULL) == cyclicListNullPointer;
    deleteCyclicList(&emptyCyclicList);
    return testResult ? testPassed : testFailed;
}

int main(void)
{
    if (test1() != testPassed)
    {
        printf("First test failed\n");
        return testFailed;
    }
    printf("First test passed\n");
    if (test2() != testPassed)
    {
        printf("Second test failed\n");
        return testFailed;
    }
    printf("Second test passed\n");
    return testPassed;
}
