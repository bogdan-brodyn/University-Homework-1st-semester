#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../Task2/CheckArrayForNumber.h"

typedef enum
{
    defaultErrorCode,
    testFailed
} ErrorCode;

bool testCheckArrayForNumber(void)
{
    const size_t testCount = 9;
    const size_t testArraySize = 5;
    const int testArray[] = { 1, 2, 3, 4, 5 };
    const int testNumber[] = { 0, 1, 2, 3, 4, 5, 6, 7, 10423 };
    const bool result[] = { false, true, true, true, true, true, false, false, false };
    for (size_t i = 0; i < testCount; ++i)
    {
        if (checkArrayForNumber(testArray, testArraySize, testNumber[i]) != result[i])
        {
            return false;
        }   
    }
    return true;
}

int main(void)
{
    if (!testCheckArrayForNumber())
    {
        printf("Sorry, the program is not working correctly\n");
        return testFailed;
    }
    printf("The program has been successfully tested\n");
    return defaultErrorCode;
}
