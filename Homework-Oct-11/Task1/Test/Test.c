#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <locale.h>
#include <time.h>

#include "../Task1/BinaryRepresentation.h"

typedef enum
{
    testPassed,
    testFailed,
    errorDuringExecution
} TestResult;

TestResult testGetRepresentationFunctions(void)
{
    const int testLeftBorder = -100000;
    const int testRightBorder = 100000;
    for (int i = testLeftBorder; i < testRightBorder; ++i)
    {
        char test[NUMBER_SIZE];
        getBinaryNumberRepresentation(i, test);
        if (i != getDecimalRepresentation(test))
        {
            return testFailed;
        }
    }
    return testPassed;
}

TestResult testAddNumbersBinaryRepresentation(void)
{
    const int randomTestCount = 100000;
    for (int i = 0; i < randomTestCount; ++i)
    {
        const int number1 = rand() % INT_MAX;
        const int number2 = rand() % INT_MAX;
        char binaryNumber1[NUMBER_SIZE];
        char binaryNumber2[NUMBER_SIZE];
        getBinaryNumberRepresentation(number1, binaryNumber1);
        getBinaryNumberRepresentation(number2, binaryNumber2);
        char binarySum[NUMBER_SIZE];
        addNumbersBinaryRepresentation(binaryNumber1, binaryNumber2, binarySum);
        if (number1 + number2 != getDecimalRepresentation(binarySum))
        {
            return testFailed;
        }
    }
    return testPassed;
}

int main(void)
{
    setlocale(LC_ALL, "Russian");

    srand(time(NULL));

    if (testGetRepresentationFunctions() != testPassed)
    {
        printf("Программа работает некорректно.\n");
        printf("Перевод чисел из двоичной системы счисления в десятичную и наоборот выдал ошибку\n");
        return testFailed;
    }
    if (testAddNumbersBinaryRepresentation() != testPassed)
    {
        printf("Программа работает некорректно.\n");
        printf("Сложение чисел выдаёт неверный результат\n");
        return testFailed;
    }
    printf("Программа успешно прошла тестирование.\n");

    return testPassed;
}
