#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <locale.h>

#define numberSize sizeof(int) * 8

// It is necessary to pass an array to the function to write a binary number representation to it
void getBinaryNumberRepresentation(const int number, int binaryNumberRepresentation[numberSize])
{
	for (int i = numberSize - 1; i >= 0; --i)
	{
		binaryNumberRepresentation[numberSize - 1 - i] = (number >> i) & 1;
	}
}

int getDecimalRepresentation(const int binaryNumber[numberSize])
{
	int res = 0;
	for (int i = numberSize - 1; i >= 0; --i)
	{
		res += binaryNumber[i] << (numberSize - 1 - i);
	}
	return res;
}

// It is necessary to pass an array to the function to write a binary sum representation to it
// Returns 1 if an overflow occurred
int addNumbersBinaryRepresentation(const int binaryNumber1[numberSize], 
	const int binaryNumber2[numberSize], int binarySumRepresentation[numberSize])
{
	for (int i = numberSize - 1; i >= 0; --i)
	{
		binarySumRepresentation[i] = binaryNumber1[i] + binaryNumber2[i];
	}

	for (int i = numberSize - 1; i >= 0; --i)
	{
		if (binarySumRepresentation[i] >= 2)
		{
			binarySumRepresentation[i] -= 2;
			if (i == 0)
			{
				return 1;
			}
			binarySumRepresentation[i - 1] += 1;
		}
	}
	return 0;
}

void printBinaryNumber(const int binaryNumber[numberSize])
{
	for (int i = 0; i < numberSize; ++i)
	{
		printf("%d", binaryNumber[i]);
	}
	printf("\n");
}

int testGetRepresentationFunctions(void)
{
	for (int i = -100000; i < 100000; ++i)
	{
		int test[numberSize];
		getBinaryNumberRepresentation(i, test);
		if (i != getDecimalRepresentation(test))
		{
			return 1;
		}
	}
	return 0;
}

int testAddNumbersBinaryRepresentation(void)
{
	for (int i = 0; i < 100000; ++i)
	{
		int number1 = rand() % INT_MAX;
		int number2 = rand() % INT_MAX;
		int binaryNumber1[numberSize];
		int binaryNumber2[numberSize];
		getBinaryNumberRepresentation(number1, binaryNumber1);
		getBinaryNumberRepresentation(number2, binaryNumber2);
		int binarySum[numberSize];
		addNumbersBinaryRepresentation(binaryNumber1, binaryNumber2, binarySum);
		if (number1 + number2 != getDecimalRepresentation(binarySum))
		{
			return 1;
		}
	}
	return 0;
}

int main(void)
{
	setlocale(LC_ALL, "Russian");

	if (testGetRepresentationFunctions() != 0)
	{
		printf("Программа работает некорректно.\n");
		printf("Перевод чисел из двоичной системы счисления в десятичную и наоборот выдал ошибку\n");
		return 1;
	}
	if (testAddNumbersBinaryRepresentation() != 0)
	{
		printf("Программа работает некорректно.\n");
		printf("Сложение чисел выдаёт неверный результат\n");
		return 2;
	}
	printf("Программа успешно прошла тестирование.\n");

	printf("Программа переводит два введённых пользователем числа в двоичное представление в дополнительном коде и печатает.\n");
	printf("Складывает их в двоичном представлении, выводит сумму в двоичном представлении.\n");
	printf("Переводит сумму в десятичное представление, печатает.\n");
	int a = 0;
	printf("Введите первое число: ");
	scanf_s("%d", &a);
	int b = 0;
	printf("Введите второе число: ");
	scanf_s("%d", &b);

	int binaryA[numberSize] = { 0 };
	getBinaryNumberRepresentation(a, binaryA);
	printf("Первое число в двоичном представлении: ");
	printBinaryNumber(binaryA);

	int binaryB[numberSize] = { 0 };
	getBinaryNumberRepresentation(b, binaryB);
	printf("Второе число в двоичном представлении: ");
	printBinaryNumber(binaryB);

	int binarySumAB[numberSize] = { 0 };
	int errorCode = addNumbersBinaryRepresentation(binaryA, binaryB, binarySumAB);
	if (errorCode == 1)
	{
		printf("При сложении произошло переполнение.\n");
	}
	printf("Сумма чисел в двоичном представлении:  ");
	printBinaryNumber(binarySumAB);

	int sumAB = getDecimalRepresentation(binarySumAB);
	printf("Сумма чисел в десятичном виде: ");
	printf("%d\n", sumAB);
}