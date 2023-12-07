#pragma once

typedef enum
{
    countingRhymeDefaultErrorCode,
    countingRhymeMemoryLack,
    countingRhymeExecutedUrgently
} CountingRhymeErrorCode;

CountingRhymeErrorCode getLastElementValue(const int n, const int m, int* const lastElementValue);
