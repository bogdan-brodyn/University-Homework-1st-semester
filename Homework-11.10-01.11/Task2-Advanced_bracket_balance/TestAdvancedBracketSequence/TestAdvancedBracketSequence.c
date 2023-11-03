#include <stdio.h>
#include <stdbool.h>

#include "../Task2-Advanced_bracket_balance/CheckBracketSequenceCorrectness.h"

typedef enum
{
    testPassed,
    testFailed,
    testMemoryLack
} TestResult;

TestResult runTest(const char* const bracketSequences, const bool correctAnswer)
{
    bool isCorrect = !correctAnswer;
    BracketSequenceErrorCode errorCode = checkBracketSequenceCorrectness(bracketSequences, &isCorrect);
    if (errorCode == bracketSequenceMemoryLack)
    {
        return testMemoryLack;
    }
    if (isCorrect != correctAnswer)
    {
        return testFailed;
    }
    return testPassed;
}

TestResult testAdvancedBracketBalance(void)
{
    const size_t correctTestCount = 9;
    const char correctBracketSequences[][17] = { "", "()", "[]", "{}", "{()}", "([])", "[](({}))", "()()[]", "[[{({()})}]]([])" };
    for (size_t i = 0; i < correctTestCount; ++i)
    {
        TestResult testResult = runTest(correctBracketSequences[i], true);
        if (testResult != testPassed)
        {
            return testResult;
        }
    }

    const size_t incorrectTestCount = 8;
    const char incorrectBracketSequences[][6] = { "(]", "[}", "{[]", "[])", "))((", "{)(}", "[{})", "[][)]"};
    for (size_t i = 0; i < incorrectTestCount; ++i)
    {
        TestResult testResult = runTest(incorrectBracketSequences[i], false);
        if (testResult != testPassed)
        {
            return testResult;
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
