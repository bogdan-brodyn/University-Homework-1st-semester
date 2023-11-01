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

SortedList* createSortedList(void)
{
    return (SortedList*)calloc(1, sizeof(SortedList));
}

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

bool findValue(const SortedList* const sortedList, const int value)
{
    if (sortedList == NULL)
    {
        return false;
    }
    SortedListElement* currentElement = sortedList->head;
    while (currentElement != NULL)
    {
        if (currentElement->value == value)
        {
            return true;
        }
        currentElement = currentElement->next;
    }
    return false;
}

SortedListError addValue(SortedList* const sortedList, const int value)
{
    if (sortedList == NULL)
    {
        return sortedListNullPointer;
    }
    if (findValue(sortedList, value))
    {
        return sortedListDefaultErrorCode;
    }

    SortedListElement* const newElement = (SortedListElement* const)calloc(1, sizeof(SortedListElement));
    if (newElement == NULL)
    {
        return sortedListMemoryLack;
    }
    newElement->value = value;

    if (sortedList->head == NULL)
    {
        sortedList->head = newElement;
        return sortedListDefaultErrorCode;
    }
    if (sortedList->head->value > value)
    {
        newElement->next = sortedList->head;
        sortedList->head = newElement;
        return sortedListDefaultErrorCode;
    }

    SortedListElement* currentElement = sortedList->head;
    while (true)
    {
        if (currentElement->next == NULL)
        {
            currentElement->next = newElement;
            break;
        }
        if (currentElement->next->value > value)
        {
            newElement->next = currentElement->next;
            currentElement->next = newElement;
            break;
        }
        currentElement = currentElement->next;
    }
    return sortedListDefaultErrorCode;
}

SortedListError deleteValue(SortedList* const sortedList, const int value)
{
    if (sortedList == NULL)
    {
        return sortedListNullPointer;
    }
    SortedListElement* currentElement = sortedList->head;
    if (currentElement->value == value)
    {
        sortedList->head = currentElement->next;
        free(currentElement);
        return sortedListDefaultErrorCode;
    }
    while (true)
    {
        if (currentElement->next == NULL)
        {
            break;
        }
        if (currentElement->next->value == value)
        {
            SortedListElement* temp = currentElement->next;
            currentElement->next = currentElement->next->next;
            free(temp);
            break;
        }
        currentElement = currentElement->next;
    }
    return sortedListDefaultErrorCode;
}

void printSortedList(const SortedList* const sortedList)
{
    if (sortedList == NULL)
    {
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

