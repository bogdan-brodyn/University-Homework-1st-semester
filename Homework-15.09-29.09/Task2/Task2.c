#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <limits.h>
#include <float.h>

typedef enum
{
    defaultErrorCode,
    overflowMaximumInteger,
    zeroNegativeDegree,
    testFailed
} ErrorCode;

typedef double (*powerFunction)(double, int, ErrorCode*);

double checkOverflow(const double number, ErrorCode* errorCode)
{
    if (number > LLONG_MAX)
    {
        *errorCode = overflowMaximumInteger;
    }
    return number;
}

double powerLinearly(const double number, const int degree, ErrorCode* errorCode)
{
    if (number == 0 && degree < 0)
    {
        *errorCode = zeroNegativeDegree;
        return 0;
    }

    if (degree == 0)
    {
        return 1;
    }
    double result = 1;
    for (int i = 0; i < degree; ++i)
    {
        result = checkOverflow(result * number, errorCode);
    }
    for (int i = 0; i < -degree; ++i)
    {
        result /= number;
    }
    return result;
}

double powerLogarithmic(const double number, const int degree, ErrorCode* errorCode)
{
    if (number == 0 && degree < 0)
    {
        *errorCode = zeroNegativeDegree;
        return 0;
    }

    if (degree == 0)
    {
        return 1;
    }
    if (degree == 1)
    {
        return number;
    }
    if (degree == -1)
    {
        return 1 / number;
    }
    if (degree < 0)
    {
        if (degree % 2 == 0)
        {
            return powerLogarithmic(1 / (number * number), degree / 2, errorCode);
        }
        return (1 / number) * powerLogarithmic(number, degree + 1, errorCode);
    }
    if (degree % 2 == 0)
    {
        return checkOverflow(
            powerLogarithmic(number * number, degree / 2, errorCode), errorCode);
    }
    return checkOverflow(
        number * powerLogarithmic(number, degree - 1, errorCode), errorCode);
}

int testErrorCodeCorrectness(const double number, const int degree, const powerFunction powerFunction, const ErrorCode correctErrorCode)
{
    ErrorCode testErrorCode = defaultErrorCode;
    powerFunction(number, degree, &testErrorCode);
    if (testErrorCode != correctErrorCode)
    {
        return testFailed;
    }
    return defaultErrorCode;
}

ErrorCode testPowerFunctionsErrorCodes(void)
{
    bool codesAreCorrect =
        testErrorCodeCorrectness(2, 100, powerLinearly, overflowMaximumInteger) == defaultErrorCode
        && testErrorCodeCorrectness(2, 100, powerLogarithmic, overflowMaximumInteger) == defaultErrorCode
        && testErrorCodeCorrectness(0, -1, powerLinearly, zeroNegativeDegree) == defaultErrorCode
        && testErrorCodeCorrectness(0, -1, powerLogarithmic, zeroNegativeDegree) == defaultErrorCode;
    return codesAreCorrect ? defaultErrorCode : testFailed;
}

ErrorCode testPowerFunctionsWorkTheSame(void)
{
    if (testPowerFunctionsErrorCodes != defaultErrorCode)
    {
        return testFailed;
    }

    for (int number = -20; number < 20; number++)
    {
        for (int degree = 0; degree < 13; degree++)
        {
            ErrorCode errorCodeLinear = defaultErrorCode;
            ErrorCode errorCodeLogarithmic = defaultErrorCode;
            if (powerLinearly(number, degree, &errorCodeLinear) !=
                powerLogarithmic(number, degree, &errorCodeLogarithmic)
                || errorCodeLinear != defaultErrorCode || errorCodeLogarithmic != defaultErrorCode)
            {
                return testFailed;
            }
        }
    }

    for (int number = -100; number < 100; number++)
    {
        for (int degree = -1000; degree < 0; degree++)
        {
            ErrorCode errorCodeLinear = defaultErrorCode;
            ErrorCode errorCodeLogarithmic = defaultErrorCode;
            if (abs(powerLinearly(number, degree, &errorCodeLinear)
                - powerLogarithmic(number, degree, &errorCodeLogarithmic)) > 1e9
                || errorCodeLinear != defaultErrorCode || errorCodeLogarithmic != defaultErrorCode)
            {
                return testFailed;
            }
        }
    }

    return defaultErrorCode;
}

const char linear[] = "Linear";
const char logarithmic[] = "Logarithmic";

void demonstrateFunctionToUser(const int number, const int degree, const powerFunction powerFunction, const char functionName[])
{
    ErrorCode errorCode = defaultErrorCode;
    clock_t begin = clock();
    double ans = powerFunction(number, degree, &errorCode);
    clock_t end = clock();
    if (errorCode != defaultErrorCode)
    {
        printf("%s algotithm terminated with an error\n", functionName);
        return;
    }
    printf("%s algotithm returned: %.20f. Approximate execution time: %ld\n", functionName, ans, end - begin);
}

int main(void)
{
    if (!testPowerFunctionsWorkTheSame())
    {
        printf("Sorry, program is working incorrectly\n");
        return testFailed;
    }
    printf("Program is working correctly\n");

    int number = 0;
    printf("number = ");
    scanf_s("%d", &number);
    int degree = 0;
    printf("degree = ");
    scanf_s("%d", &degree);

    demonstrateFunctionToUser(number, degree, powerLinearly, linear);
    demonstrateFunctionToUser(number, degree, powerLogarithmic, logarithmic);
}
