#include <stdio.h>

#include "../CyclicList/CyclicList.h"
#include "CountingRhyme.h"

int main(void)
{
    printf("n warriors participate and kill every mth\n");
    size_t n = 0;
    printf("Enter n: ");
    scanf_s("%ld", &n);
    size_t m = 0;
    printf("Enter m: ");
    scanf_s("%ld", &m);

    int k = 0;
    CountingRhymeErrorCode errorCode = getLastElementValue(n, m, &k);
    if (errorCode != countingRhymeDefaultErrorCode)
    {
        printf("The program has executed urgently\n");
    }
    else
    {
        printf("The warrior with the starting position %d will remain last\n", k);
    }
    return errorCode;
}
