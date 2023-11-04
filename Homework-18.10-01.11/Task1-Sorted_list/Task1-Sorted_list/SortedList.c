#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "SortedList.h"

typedef struct SortedListElement
{
    int value;
    struct SortedListElement* next;
} SortedListElement;

struct SortedList
{
    SortedListElement* head;
};

void deleteSortedList(SortedList** const sortedList)
{
    if (sortedList == NULL)
    {
        return;
    }
    while (!isEmpty(*sortedList))
    {
        deleteValue(*sortedList, (*sortedList)->head->value);
    }
    free(*sortedList);
    *sortedList = NULL;
}

SortedListError addValue(SortedList** const sortedList, const int value)
{
    if (sortedList == NULL)
    {
        return sortedListNullPointer;
    }
    if (*sortedList == NULL)
    {
        *sortedList = (SortedList* const)calloc(1, sizeof(sortedList));
        if (*sortedList == NULL)
        {
            return sortedListMemoryLack;
        }
    }

    SortedListElement* const newElement = (SortedListElement* const)calloc(1, sizeof(SortedListElement));
    if (newElement == NULL)
    {
        return sortedListMemoryLack;
    }
    newElement->value = value;

    newElement->next = (*sortedList)->head;
    (*sortedList)->head = newElement;
    for (SortedListElement* currentElement = (*sortedList)->head; currentElement->next != NULL 
        && currentElement->next->value < currentElement->value; currentElement = currentElement->next)
    {
        currentElement->value = currentElement->next->value;
        currentElement->next->value = value;
    }
    return sortedListDefaultErrorCode;
}

void deleteValue(SortedList* const sortedList, const int value)
{
    if (sortedList == NULL)
    {
        return;
    }
    SortedListElement* currentElement = sortedList->head;
    if (currentElement->value == value)
    {
        sortedList->head = currentElement->next;
        free(currentElement);
        return;
    }
    for (; currentElement->next != NULL; currentElement = currentElement->next)
    {
        if (currentElement->next->value == value)
        {
            SortedListElement* temp = currentElement->next;
            currentElement->next = currentElement->next->next;
            free(temp);
            break;
        }
    }
}

void printSortedList(const SortedList* const sortedList)
{
    if (sortedList == NULL)
    {
        printf("\n");
        return;
    }
    for (SortedListElement* currentElement = sortedList->head; currentElement != NULL; currentElement = currentElement->next)
    {
        printf("%d ", currentElement->value);
    }
    printf("\n");
}

bool isEmpty(const SortedList* const sortedList)
{
    return sortedList == NULL || sortedList->head == NULL;
}

bool compareList(const SortedList* const sortedList, const int* const arrayToCompare, const size_t arrayToCompareSize)
{
    if (sortedList == NULL || arrayToCompare == NULL)
    {
        return sortedList == arrayToCompare;
    }
    size_t arrayToComparePointer = 0;
    for (SortedListElement* currentElement = sortedList->head; currentElement != NULL; currentElement = currentElement->next, ++arrayToComparePointer)
    {
        if (arrayToComparePointer >= arrayToCompareSize || currentElement->value != arrayToCompare[arrayToComparePointer])
        {
            return false;
        }
    }
    return arrayToComparePointer == arrayToCompareSize;
}
