#include <stdlib.h>

#include "GetMostCommonNumber.h"

// comparator for quick sorting
int compare(const void* const element1, const void* const element2)
{
    const int firstElement = *((const int* const)element1);
    const int secondElement = *((const int* const)element2);
    return firstElement - secondElement;
}

int getMostCommonNumber(const int* const array, const size_t arraySize, ErrorCode* errorCode)
{
    int* const arrayCopy = (int* const)malloc(sizeof(int) * arraySize);
    if (arrayCopy == NULL)
    {
        *errorCode = memoryLack;
        return 0;
    }
    for (size_t i = 0; i < arraySize; ++i)
    {
        arrayCopy[i] = array[i];
    }
    qsort(arrayCopy, arraySize, sizeof(int), compare);
    return getMostCommonNumberFromSortedArray(arrayCopy, arraySize);
}

int getMostCommonNumberFromSortedArray(const int* const array, const size_t arraySize)
{
    size_t currentLength = 1;
    size_t maxLength = 0;
    int mostCommonNumber = 0;
    for (size_t i = 1; i < arraySize; ++i)
    {
        if (array[i] == array[i - 1])
        {
            ++currentLength;
            continue;
        }
        if (currentLength > maxLength)
        {
            maxLength = currentLength;
            mostCommonNumber = array[i - 1];
        }
        currentLength = 1;
    }
    if (currentLength > maxLength)
    {
        maxLength = currentLength;
        mostCommonNumber = array[arraySize - 1];
    }
    return mostCommonNumber;
}
