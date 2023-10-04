#include <stdio.h>
#include <stdlib.h>

// returns the most common number in the array
// array needs to be sorted
int getMostCommonNumber(const int* array, const int arraySize)
{
	int currentLength = 1;
	int maxLength = 0;
	int mostCommonNumber = 0;
	for (int i = 1; i < arraySize; ++i)
	{
		if (array[i] == array[i - 1])
		{
			++currentLength;
		}
		else if (currentLength > maxLength)
		{
			maxLength = currentLength;
			mostCommonNumber = array[i - 1];
			currentLength = 1;
		}
	}
	if (currentLength > maxLength)
	{
		maxLength = currentLength;
		mostCommonNumber = array[arraySize - 1];
	}
	return mostCommonNumber;
}

// comparator for quick sorting
int comp(const void* element1, const void* element2)
{
	int firstElement = *((int*)element1);
	int secondElement = *((int*)element2);
	return (firstElement > secondElement) - (firstElement < secondElement);
}

int testGetMostCommonNumber(void)
{
	int testArray[][7] = { {1}, {2, 2}, {1, 2, 2}, {3, 3, 2, 1}, {3, 2, 1, 2, 3, 4, 2} };
	const int testArraySize[] = { 1, 2, 3, 4, 7 };
	const int correctResult[] = { 1, 2, 2, 3, 2 };
	for (int testIndex = 0; testIndex < 5; ++testIndex)
	{
		qsort(testArray[testIndex], testArraySize[testIndex], sizeof(int), comp);
		if (getMostCommonNumber(testArray[testIndex], testArraySize[testIndex]) != correctResult[testIndex])
		{
			return testIndex + 1;
		}
	}
	return 0;
}

int main(void)
{
	const int errorCode = testGetMostCommonNumber();
	if (errorCode != 0)
	{
		printf("The program gave an incorrect answer on test %d\n", errorCode);
		return errorCode;
	}
	printf("The program has passed all the tests\n");
}