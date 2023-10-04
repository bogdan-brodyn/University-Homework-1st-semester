#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// returns true if the array contains a number. Otherwise - false
// array needs to be sorted. It's a binary search
bool checkArrayForNumber(const int* arrayToCheck, const int arraySize, const int number)
{
	int leftSearchBorder = -1;
	int rightSearchBorder = arraySize;
	while (leftSearchBorder < rightSearchBorder - 1)
	{
		int middle = (leftSearchBorder + rightSearchBorder) / 2;
		if (arrayToCheck[middle] < number)
		{
			leftSearchBorder = middle;
		}
		else
		{
			rightSearchBorder = middle;
		}
	}
	return rightSearchBorder != arraySize && arrayToCheck[rightSearchBorder] == number;
}

bool testCheckArrayForNumber(void)
{
	const int testArray[] = { 1, 2, 3, 4, 5 };
	const int testNumber[] = { 0, 1, 2, 3, 4, 5, 6, 7, 10423 };
	const bool result[] = { false, true, true, true, true, true, false, false, false };
	for (int i = 0; i < 9; ++i)
	{
		if (checkArrayForNumber(testArray, 5, testNumber[i]) != result[i])
		{
			return false;
		}
	}
	return true;
}

// comparator for quick sorting
int comp(const void* element1, const void* element2)
{
	int firstElement = *((int*)element1);
	int secondElement = *((int*)element2);
	return (firstElement > secondElement) - (firstElement < secondElement);
}

int main(void)
{
	if (!testCheckArrayForNumber())
	{
		printf("Sorry, the program is not working correctly\n");
		return 1;
	}

	printf("Program generates a random numbers array of length n and random k numbers.\n");
	printf("Searches for these numbers in the array, outputs the number of found ones to the console\n");
	int n = 0;
	printf("n = ");
	scanf_s("%d", &n);
	int k = 0;
	printf("k = ");
	scanf_s("%d", &k);
	int* array = (int*)malloc(sizeof(int) * n);
	if (array == NULL)
	{
		printf("The program ended urgently due to lack of memory\n");
		return 2;
	}
	for (int i = 0; i < n; ++i)
	{
		array[i] = rand();
	}

	qsort(array, n, sizeof(int), comp);

	int foundNumbersCounter = 0;
	for (int i = 0; i < k; ++i)
	{
		int randomNumber = rand();
		foundNumbersCounter += checkArrayForNumber(array, n, randomNumber);
	}
	printf("Random array of length %d contains %d of %d random numbers\n", n, foundNumbersCounter, k);
	free(array);
}