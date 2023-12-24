#include <stdio.h>

#include "Lexer.h"

int test(void)
{
    const size_t testCasesCount = 6;
    const char* const correctTestCases[] = { "1", "123", "12.4", "23e17", 
        "43.254e858", "26E-1" };
    for (size_t i = 0; i < testCasesCount; ++i)
    {
        if (!isNumber(correctTestCases[i]))
        {
            return i + 1;
        }
    }
    char* incorrectTestCases[] = { "", "ab", "12.", "e17", "43.254e", "26E-" };
    for (size_t i = 0; i < testCasesCount; ++i)
    {
        if (isNumber(incorrectTestCases[i]))
        {
            return i + 1 + testCasesCount;
        }
    }
    return 0;
}

int main(void)
{
    int testResult = test();
    printf(testResult == 0 ? "Program has passed all the tests\n" : 
        "Program has failed test: %d\n", testResult);
    return testResult == 0;
}
