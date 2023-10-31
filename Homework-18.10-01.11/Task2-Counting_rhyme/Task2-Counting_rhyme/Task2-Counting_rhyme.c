#include <stdio.h>

#include "../CyclicList/CyclicList.h"
#include "CountingRhyme.h"

int main(void)
{
    printf("n warriors participate and kill every mth\n");
    int n = 0;
    printf("Enter n: ");
    scanf_s("%d", &n);
    int m = 0;
    printf("Enter m: ");
    scanf_s("%d", &m);

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
