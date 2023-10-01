#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <windows.h>

int getFibonacciNumberRecursively(int numberPosition, int* errorCode)
{
    if (numberPosition <= 0)
    {
        *errorCode = 1;
        return -1;
    }
    if (numberPosition <= 2)
    {
        return 1;
    }
    return getFibonacciNumberRecursively(numberPosition - 1, errorCode)
        + getFibonacciNumberRecursively(numberPosition - 2, errorCode);
}

int getFibonacciNumberIteratively(int numberPosition, int* errorCode)
{
    if (numberPosition <= 0)
    {
        *errorCode = 1;
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
    for (int numberPosition = 1; numberPosition < 30; ++numberPosition)
    {
        int errorCodeIterative = 0;
        int errorCodeRecursive = 0;
        if (getFibonacciNumberIteratively(numberPosition, &errorCodeIterative)
            != getFibonacciNumberRecursively(numberPosition, &errorCodeIterative)
            || errorCodeIterative != 0 || errorCodeRecursive != 0)
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
        return 1;
    }
    printf("Program is working correctly\n");
    printf("Program will display on the screen approximate execution time for few fibonachi numbers\n\n");
    Sleep(1500);

    for (int i = 25; i < 40; ++i)
    {
        printf("For number with position %d\n", i);
        int errorCode = 0;
        clock_t begin = clock();
        getFibonacciNumberIteratively(i, &errorCode);
        clock_t end = clock();
        if (errorCode != 0)
        {
            printf("Iterative version terminated with an error\n");
            return 2;
        }
        printf("%d for iterative version and ", end - begin);

        begin = clock();
        getFibonacciNumberRecursively(i, &errorCode);
        end = clock();
        if (errorCode != 0)
        {
            printf("Recursive version terminated with an error\n");
            return 2;
        }
        printf("%d for recursive version\n\n", end - begin);
        Sleep(700);
    }
    printf("Starting from position 40, recursive version is too slow\n\n");
}