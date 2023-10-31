#include <stdio.h>
#include <stdbool.h>

#include "../Task2-Advanced_bracket_balance/CheckBracketSequenceCorrectness.h"

typedef enum
{
    testPassed,
    testFailed,
    testMemoryLack
} TestResult;

TestResult testAdvancedBracketBalance(void)
{
    const int correctTestCount = 9;
    const char correctBracketSequences[][17] = { "", "()", "[]", "{}", "{()}", "([])", "[](({}))", "()()[]", "[[{({()})}]]([])" };
    for (size_t i = 0; i < correctTestCount; ++i)
    {
        bool isCorrect = false;
        BracketSequenceErrorCode errorCode = checkBracketSequenceCorrectness(correctBracketSequences[i], &isCorrect);
        if (errorCode == bracketSequenceMemoryLack)
        {
            return testMemoryLack;
        }
        if (isCorrect != true)
        {
            return testFailed;
        }
    }

    const int incorrectTestCount = 8;
    const char incorrectBracketSequences[][6] = { "(]", "[}", "{[]", "[])", "))((", "{)(}", "[{})", "[][)]"};
    for (size_t i = 0; i < incorrectTestCount; ++i)
    {
        bool isCorrect = true;
        BracketSequenceErrorCode errorCode = checkBracketSequenceCorrectness(incorrectBracketSequences[i], &isCorrect);
        if (errorCode == bracketSequenceMemoryLack)
        {
            return testMemoryLack;
        }
        if (isCorrect != false)
        {
            return testFailed;
        }
    }
    return true;
}

int main(void)
{
    TestResult testResult = testAdvancedBracketBalance();
    if (testResult == testMemoryLack)
    {
        printf("Test executed urgently because of memory lack\n");
    }
    if (testResult == testFailed)
    {
        printf("Program has not passed the test\n");
    }
    printf("Program has passed all the tests\n");
    return testPassed;
}
