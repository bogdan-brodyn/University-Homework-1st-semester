#include <stdio.h>
#include <stdbool.h>

#include "../Task1-Postfix_calculator/Postfix_calculator.h"

typedef enum
{
    testPassed,
    testFailed
} TestErrorCode;

bool test(void)
{
    const int correctTestCount = 6;
    const char correctMathExpressions[][14] = { "1", "1 2 -", "3 2 1 + *", "9 6 - 1 2 + *", "0 1 + 1 + 1 +", "1 2 3 * 2 * *" };
    const int correctResults[] = { 1, -1, 9, 9, 3, 12 };
    for (size_t i = 0; i < correctTestCount; ++i)
    {
        int testResult = 0;
        CalculatorErrorCode errorCode = getMathExpressionResult(correctMathExpressions[i], &testResult);
        if (testResult != correctResults[i] || errorCode != calculatorDefaultErrorCode)
        {
            return false;
        }
    }

    const int incorrectTestCount = 5;
    const char incorrectMathExpressions[][10] = { "1 - 2", "- 1 2", "3 2 1 +", "1 2", "3 8 * * 2" };
    for (size_t i = 0; i < incorrectTestCount; ++i)
    {
        int testResult = 0;
        CalculatorErrorCode errorCode = getMathExpressionResult(incorrectMathExpressions[i], &testResult);
        if (errorCode != calculatorInvalidInput)
        {
            return false;
        }
    }

    return true;
}

int main(void)
{
    if (!test())
    {
        printf("Program has failed tests\n");
        return testFailed;
    }
    printf("Program has passed all the tests\n");
    return testPassed;
}
