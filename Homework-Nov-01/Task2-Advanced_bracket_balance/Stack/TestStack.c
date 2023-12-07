#include <stdio.h>
#include <stdlib.h>

#include "Stack.h"

typedef enum
{
    testPassed,
    testFailed,
    testMemoryLack
} TestResult;

static TestResult test1(void)
{
    Stack* const stack = createStack();
    if (stack == NULL)
    {
        return testMemoryLack;
    }
    char topElement1 = 0;
    char topElement2 = 0;
    char topElement3 = 0;
    bool testResult =
        push(stack, 1) == defaultErrorCode
        && push(stack, 2) == defaultErrorCode
        && push(stack, 3) == defaultErrorCode
        && top(stack, &topElement1) == defaultErrorCode
        && pop(stack) == defaultErrorCode
        && top(stack, &topElement2) == defaultErrorCode
        && pop(stack) == defaultErrorCode
        && top(stack, &topElement3) == defaultErrorCode
        && pop(stack) == defaultErrorCode
        && topElement1 == 3
        && topElement2 == 2
        && topElement3 == 1;
    deleteStack(&stack);
    return testResult && stack == NULL ? testPassed : testFailed;
}

static TestResult test2(void)
{
    Stack* const nullStack = NULL;
    Stack* const emptyStack = createStack();
    if (emptyStack == NULL)
    {
        return testMemoryLack;
    }
    char topElement1 = 0;
    char topElement2 = 0;
    bool testResult =
        push(NULL, 1) == nullPtr
        && pop(NULL) == nullPtr
        && top(NULL, &topElement1) == nullPtr
        && topElement1 == 0
        && pop(emptyStack) == stackEmpty
        && top(emptyStack, &topElement1) == stackEmpty
        && topElement2 == 0;
    deleteStack(&emptyStack);
    return testResult ? testPassed : testFailed;
}

static void printTestResult(const char* const testName, TestResult(*testFuction)(void))
{
    printf(testFuction() == testPassed ? "%s test passed\n" : "%s test failed\n", testName);
}

int main(void)
{
    printTestResult("First", test1);
    printTestResult("Second", test2);
}
