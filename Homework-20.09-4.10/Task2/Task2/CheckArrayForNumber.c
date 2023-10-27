#include <stdlib.h>
#include <stdbool.h>

#include "CheckArrayForNumber.h"

// returns true if the array contains a number. Otherwise - false
// array needs to be sorted. It's a binary search
bool checkArrayForNumber(const int* const arrayToCheck, const size_t arraySize, const int number)
{
    size_t leftSearchBorder = 0;
    size_t rightSearchBorder = arraySize - 1;
    while (leftSearchBorder < rightSearchBorder - 1)
    {
        size_t middle = (leftSearchBorder + rightSearchBorder) / 2;
        if (arrayToCheck[middle] < number)
        {
            leftSearchBorder = middle;
        }
        else
        {
            rightSearchBorder = middle;
        }
    }
    return arrayToCheck[leftSearchBorder] == number || number == arrayToCheck[rightSearchBorder];
}
