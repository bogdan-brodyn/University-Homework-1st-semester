#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <windows.h>

typedef enum
{
    completedCorrectly,
    testsFailed,
    invalidInput
} ErrorCode;

int getFibonacciNumberRecursively(int numberPosition, ErrorCode* errorCode)
{
    if (numberPosition <= 0)
    {
        *errorCode = invalidInput;
        return -1;
    }
    if (numberPosition <= 2)
    {
        return 1;
    }
    return getFibonacciNumberRecursively(numberPosition - 1, errorCode)
        + getFibonacciNumberRecursively(numberPosition - 2, errorCode);
}

int getFibonacciNumberIteratively(int numberPosition, ErrorCode* errorCode)
{
    if (numberPosition <= 0)
    {
        *errorCode = invalidInput;
        return -1;
    }
    int currentFibonachiNumber = 1;     // it's a second fibonachi number by default
    int previousFibonacciNumber = 1;    // it's a first fibonachi number by default
    for (int i = 3; i <= numberPosition; ++i)
    {
        currentFibonachiNumber = currentFibonachiNumber + previousFibonacciNumber;
        previousFibonacciNumber = currentFibonachiNumber - previousFibonacciNumber;
    }
    return currentFibonachiNumber;
}

bool testFibonachiFunctionsWorkTheSame(void)
{
    ErrorCode errorCode = completedCorrectly;
    getFibonacciNumberIteratively(-1, &errorCode);
    if (errorCode != invalidInput)
    {
        return false;
    }
    getFibonacciNumberRecursively(-1, &errorCode);
    if (errorCode != invalidInput)
    {
        return false;
    }

    for (int numberPosition = 1; numberPosition < 30; ++numberPosition)
    {
        ErrorCode errorCodeIterative = completedCorrectly;
        ErrorCode errorCodeRecursive = completedCorrectly;
        if (getFibonacciNumberIteratively(numberPosition, &errorCodeIterative)
            != getFibonacciNumberRecursively(numberPosition, &errorCodeRecursive)
            || errorCodeIterative != completedCorrectly 
            || errorCodeRecursive != completedCorrectly)
        {
            return false;
        }
    }
    return true;
}

int main(void)
{
    printf("Please, wait the program is being checked...\n");
    if (!testFibonachiFunctionsWorkTheSame())
    {
        printf("Sorry, program is working incorrectly\n");
        return testsFailed;
    }
    printf("Program is working correctly\n");
    printf("Program will display on the screen approximate execution time for few fibonachi numbers\n\n");
    Sleep(1500);

    for (int numberPosition = 25; ; ++numberPosition)
    {
        printf("For number with position %d the number of clock ticks is:\n", numberPosition);
        ErrorCode errorCode = completedCorrectly;
        clock_t begin = clock();
        getFibonacciNumberIteratively(numberPosition, &errorCode);
        clock_t end = clock();
        if (errorCode != completedCorrectly)
        {
            printf("\nIterative version terminated with an error\n");
            return errorCode;
        }
        printf("%d for iterative version ", end - begin);

        begin = clock();
        getFibonacciNumberRecursively(numberPosition, &errorCode);
        end = clock();
        if (errorCode != completedCorrectly)
        {
            printf("\nRecursive version terminated with an error\n");
            return errorCode;
        }
        printf("and %d for recursive version\n\n", end - begin);

        if (end - begin > 1000)
        {
            printf("Starting from position %d, recursive version is too slow\n\n", numberPosition);
            break;
        }
        Sleep(700);
    }
    return completedCorrectly;
}
