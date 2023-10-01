#include <stdio.h>
#include <stdbool.h>
#include <time.h>

#define modulo 1000000007

long long powerLinearly(long long number, int degree, int* errorCode)
{
    if (degree < 0)
    {
        *errorCode = 1;
        return -1;
    }
    if (degree == 0)
    {
        return 1;
    }
    number %= modulo;
    long long result = 1;
    for (int i = 0; i < degree; ++i)
    {
        result *= number;
        result %= modulo;
    }
    return result;
}

long long powerLogarithmic(long long number, int degree, int* errorCode)
{
    if (degree < 0)
    {
        *errorCode = 1;
        return -1;
    }
    if (degree == 0)
    {
        return 1;
    }
    number %= modulo;
    if (degree == 1)
    {
        return number;
    }
    if (degree % 2 == 0)
    {
        return powerLogarithmic(number * number, degree / 2, errorCode);
    }
    return (number * powerLogarithmic(number, degree - 1, errorCode)) % modulo;
}

bool testPowerFunctionsWorkTheSame(void)
{
    for (int number = 0; number < 500; number++)
    {
        for (int degree = 0; degree < 500; degree++)
        {
            int errorCodeLinear = 0;
            int errorCodeLogarithmic = 0;
            if (powerLinearly(number, degree, &errorCodeLinear)
                != powerLogarithmic(number, degree, &errorCodeLogarithmic)
                || errorCodeLinear != 0 || errorCodeLogarithmic != 0)
            {
                return false;
            }
        }
    }
    return true;
}

int main(void)
{
    if (!testPowerFunctionsWorkTheSame())
    {
        printf("Sorry, program is working incorrectly\n");
        return 1;
    }
    printf("Program is working correctly\n");
    printf("Program returns: (number^degree) mod %d\n", modulo);
    int number = 0;
    printf("number = ");
    scanf_s("%d", &number);
    int degree = 0;
    printf("degree = ");
    scanf_s("%d", &degree);

    int errorCode = 0;
    clock_t begin = clock();
    int ans = powerLinearly(number, degree, &errorCode);
    clock_t end = clock();
    if (errorCode != 0)
    {
        printf("Linear algotithm terminated with an error\n");
        return 2;
    }
    printf("Linear algotithm returned: %d. Approximate execution time: %d\n", ans, end - begin);
    begin = clock();
    ans = powerLogarithmic(number, degree, &errorCode);
    end = clock();
    if (errorCode != 0)
    {
        printf("Logarithmic algotithm terminated with an error\n");
        return 2;
    }
    printf("Logarithmic algotithm returned: %d. Approximate execution time: %d\n\n", ans, end - begin);
}