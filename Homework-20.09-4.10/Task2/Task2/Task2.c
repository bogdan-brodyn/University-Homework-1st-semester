#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "CheckArrayForNumber.h"

typedef enum
{
	defaultErrorCode,
	memoryLack
} ErrorCode;

// comparator for quick sorting
int comp(const void* element1, const void* element2)
{
	int firstElement = *((int*)element1);
	int secondElement = *((int*)element2);
	return firstElement - secondElement;
}

int main(void)
{
	srand(time(NULL));

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
		return memoryLack;
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
