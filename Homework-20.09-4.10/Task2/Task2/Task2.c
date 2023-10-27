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
int comp(const void* const element1, const void* const element2)
{
    int firstElement = *((int*)element1);
    int secondElement = *((int*)element2);
    return firstElement - secondElement;
}

int main(void)
{
    srand(time(NULL));

    printf("Program generates a random numbers array of length n and random k numbers. All numbers are in range 1:n\n");
    printf("Searches for these numbers in the array, outputs the number of found ones to the console\n");
    size_t n = 0;
    printf("n = ");
    scanf_s("%ld", &n);
    size_t k = 0;
    printf("k = ");
    scanf_s("%ld", &k);
    int* array = (int*)malloc(sizeof(int) * n);
    if (array == NULL)
    {
        printf("The program ended urgently due to lack of memory\n");
        return memoryLack;
    }
    for (size_t i = 0; i < n; ++i)
    {
        array[i] = rand() % n + 1;
    }

    qsort(array, n, sizeof(int), comp);

    size_t foundNumbersCounter = 0;
    for (size_t i = 0; i < k; ++i)
    {
        int randomNumber = rand() % n + 1;
        foundNumbersCounter += (size_t)checkArrayForNumber(array, n, randomNumber);
    }
    printf("Random array of length %ld contains %ld of %ld random numbers\n", n, foundNumbersCounter, k);
    free(array);
}
