#include <stdio.h>

#include "../Task2-Counting_rhyme/CountingRhyme.h"

typedef enum
{
    testPassed,
    testFailed,
    testInterrupted
} TestResult;

TestResult testCountingRhyme(void)
{
    const int testCount = 7;
    const int ns[] = { 1, 2, 3, 4, 5, 5, 5 };
    const int ms[] = { 1, 2, 2, 3, 2, 3, 7 };
    const int ks[] = { 1, 1, 3, 1, 3, 4, 4 };
    for (size_t i = 0; i < testCount; ++i)
    {
        int answer = 0;
        const CountingRhymeErrorCode errorCode = getLastElementValue(ns[i], ms[i], &answer);
        if (errorCode != countingRhymeDefaultErrorCode)
        {
            return testInterrupted;
        }
        if (answer != ks[i])
        {
            return testFailed;
        }
    }
    return testPassed;
}

int main(void)
{
    const TestResult testResult = testCountingRhyme();
    if (testResult == testInterrupted)
    {
        printf("Test had been interrupted because of error\n");
    }
    else if (testResult == testFailed)
    {
        printf("Not all the tests has been passed\n");
    }
    else
    {
        printf("The program has passed all the tests\n");
    }
    return testResult;
}
