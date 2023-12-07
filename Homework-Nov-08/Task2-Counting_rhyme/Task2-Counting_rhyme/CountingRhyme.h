#pragma once

typedef enum
{
    countingRhymeDefaultErrorCode,
    countingRhymeMemoryLack,
    countingRhymeExecutedUrgently
} CountingRhymeErrorCode;

CountingRhymeErrorCode getLastElementValue(const size_t n, const size_t m, int* const lastElementValue);
