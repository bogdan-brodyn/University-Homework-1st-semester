#pragma once

typedef enum
{
    sortedListDefaultErrorCode,
    sortedListMemoryLack,
    sortedListNullPointer
} SortedListError;

typedef struct SortedList SortedList;

SortedList* createSortedList(void);

void deleteSortedList(SortedList** const sortedList);

bool findValue(const SortedList* const sortedList, const int value);

SortedListError addValue(SortedList* const sortedList, const int value);

SortedListError deleteValue(SortedList* const sortedList, const int value);

void printSortedList(const SortedList* const sortedList);

bool isEmpty(const SortedList* const sortedList);
