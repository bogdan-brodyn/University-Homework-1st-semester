#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#include "BinaryRepresentation.h"

static void printBinaryRepresentation(const char binaryNumber[NUMBER_SIZE])
{
    for (unsigned char i = 0; i < NUMBER_SIZE; ++i)
    {
        printf("%d", binaryNumber[i]);
    }
    printf("\n");
}

int main(void)
{
    setlocale(LC_ALL, "Russian");

    printf("Программа переводит два введённых пользователем числа в двоичное представление в дополнительном коде и печатает.\n");
    printf("Складывает их в двоичном представлении, выводит сумму в двоичном представлении.\n");
    printf("Переводит сумму в десятичное представление, печатает.\n");
    int a = 0;
    printf("Введите первое число: ");
    scanf_s("%d", &a);
    int b = 0;
    printf("Введите второе число: ");
    scanf_s("%d", &b);

    char binaryA[NUMBER_SIZE];
    getBinaryNumberRepresentation(a, binaryA);
    printf("Первое число в двоичном представлении: ");
    printBinaryRepresentation(binaryA);

    char binaryB[NUMBER_SIZE];
    getBinaryNumberRepresentation(b, binaryB);
    printf("Второе число в двоичном представлении: ");
    printBinaryRepresentation(binaryB);

    char binarySumAB[NUMBER_SIZE];
    ErrorCode errorCode = addNumbersBinaryRepresentation(binaryA, binaryB, binarySumAB);
    if (errorCode == overflow)
    {
        printf("При сложении произошло переполнение.\n");
    }
    printf("Сумма чисел в двоичном представлении:  ");
    printBinaryRepresentation(binarySumAB);
    printf("Сумма чисел в десятичном виде: %d\n", getDecimalRepresentation(binarySumAB));
}
