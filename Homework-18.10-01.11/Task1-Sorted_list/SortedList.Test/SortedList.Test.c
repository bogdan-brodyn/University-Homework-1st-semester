#include <stdio.h>
#include <stdbool.h>

#include "../Task1-Sorted_list/SortedList.h"

typedef enum
{
    testPassed,
    testFailed
} TestResult;

static TestResult runTest(void)
{
    SortedList* sortedList = NULL;
    const int firstArrayToCompareWith[] = { 1, 1, 2, 3 };
    const int secondArrayToCompareWith[] = { 1, 3 };
    const int thirdArrayToCompareWith[] = { 1, 2, 3, 4, 5 };
    bool testResult =
        addValue(&sortedList, 1) == sortedListDefaultErrorCode
        && addValue(&sortedList, 2) == sortedListDefaultErrorCode
        && addValue(&sortedList, 1) == sortedListDefaultErrorCode
        && addValue(&sortedList, 3) == sortedListDefaultErrorCode
        && compareList(sortedList, firstArrayToCompareWith, 4);
    deleteValue(sortedList, 1);
    deleteValue(sortedList, 2);
    testResult &= compareList(sortedList, secondArrayToCompareWith, 2);
    testResult &=
        addValue(&sortedList, 5) == sortedListDefaultErrorCode
        && addValue(&sortedList, 2) == sortedListDefaultErrorCode
        && addValue(&sortedList, 4) == sortedListDefaultErrorCode
        && compareList(sortedList, thirdArrayToCompareWith, 5);
    deleteSortedList(&sortedList);
    return testResult && sortedList == NULL ? testPassed : testFailed;
}

int main(void)
{
    TestResult testResult = runTest();
    printf(testResult == testPassed ? "Program has passed all the tests\n" : "Program has failed the test\n");
    return testResult;
}
