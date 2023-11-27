#include <stdio.h>
#include <stdlib.h>

#include "LinkedList.h"
#include "../String/String.h"

typedef struct ListElement
{
    size_t count;
    char* string;
    struct ListElement* next;
} ListElement;

struct LinkedList
{
    ListElement* front;
};

static ListElement* createListElement(const char* const string)
{
    ListElement* newListElement = (ListElement*)calloc(1, sizeof(ListElement));
    if (newListElement == NULL)
    {
        return NULL;
    }
    newListElement->count = 1;
    newListElement->string = getStringCopy(string);
    if (newListElement->string == NULL)
    {
        free(newListElement);
        return NULL;
    }
    return newListElement;
}

static void deleteListElement(ListElement** const listElement)
{
    free((*listElement)->string);
    free(*listElement);
    *listElement = NULL;
}

LinkedListErrorCode pushString(LinkedList** const linkedList, const char* const string)
{
    if (*linkedList != NULL)
    {
        for (ListElement* current = (*linkedList)->front;
            current != NULL; current = current->next)
        {
            if (compare(current->string, string) == 0)
            {
                ++(current->count);
                return defaultLinkedListErrorCode;
            }
        }
    }
    ListElement* newListElement = createListElement(string);
    if (newListElement == NULL)
    {
        return memoryLackLinkedListErrorCode;
    }
    if (*linkedList == NULL)
    {
        *linkedList = (LinkedList*)calloc(1, sizeof(LinkedList));
        if (*linkedList == NULL)
        {
            deleteListElement(&newListElement);
            return memoryLackLinkedListErrorCode;
        }
        (*linkedList)->front = newListElement;
        return defaultLinkedListErrorCode;
    }
    newListElement->next = (*linkedList)->front;
    (*linkedList)->front = newListElement;
    return defaultLinkedListErrorCode;
}

size_t getElementCount(const LinkedList* const linkedList, const char* const string)
{
    for (ListElement* current = linkedList->front; 
        current != NULL; current = current->next)
    {
        if (compare(current->string, string) == 0)
        {
            return current->count;
        }
    }
    return 0;
}

void deleteLinkedList(LinkedList** const linkedList)
{
    if (linkedList == NULL || *linkedList == NULL)
    {
        return;
    }
    while ((*linkedList)->front != NULL)
    {
        ListElement* frontElement = (*linkedList)->front;
        (*linkedList)->front = frontElement->next;
        deleteListElement(&frontElement);
    }
    free(*linkedList);
    *linkedList = NULL;
}

void printLinkedList(const LinkedList* const linkedList)
{
    for (ListElement* current = linkedList->front;
        current != NULL; current = current->next)
    {
        printf("%s - %lld\n", current->string, current->count);
    }
}

size_t getLength(const LinkedList* const linkedList)
{
    size_t length = 0;
    for (ListElement* current = linkedList->front;
        current != NULL; current = current->next)
    {
        ++length;
    }
    return length;
}
