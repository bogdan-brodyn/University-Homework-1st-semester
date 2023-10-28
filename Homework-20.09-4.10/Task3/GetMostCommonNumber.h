#pragma once

// error codes for functions: get most common number
typedef enum
{
    defaultErrorCode,
    memoryLack
} ErrorCode;

// returns the most common number in the array
// function copies the array and sorts the copy
int getMostCommonNumber(const int* const array, const size_t arraySize, ErrorCode* const errorCode);
