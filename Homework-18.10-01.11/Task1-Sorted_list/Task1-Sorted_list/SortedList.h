#pragma once

typedef enum
{
    sortedListDefaultErrorCode,
    sortedListMemoryLack,
    sortedListNullPointer
} SortedListError;

typedef struct SortedList SortedList;

void deleteSortedList(SortedList** const sortedList);

SortedListError addValue(SortedList** const sortedList, const int value);

void deleteValue(SortedList* const sortedList, const int value);

void printSortedList(const SortedList* const sortedList);

bool isEmpty(const SortedList* const sortedList);

bool compareList(const SortedList* const sortedList, const int* const arrayToCompare, const int arrayToCompareSize);
