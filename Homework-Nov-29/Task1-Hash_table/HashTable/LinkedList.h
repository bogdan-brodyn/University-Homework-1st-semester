#pragma once

#include <stdlib.h>

typedef enum
{
    defaultLinkedListErrorCode,
    memoryLackLinkedListErrorCode
} LinkedListErrorCode;

typedef struct LinkedList LinkedList;

LinkedListErrorCode pushString(LinkedList** const linkedList, const char* const string);

size_t getElementCount(const LinkedList* const linkedList, const char* const string);

void deleteLinkedList(LinkedList** const linkedList);

void printLinkedList(const LinkedList* const linkedList);

size_t getLength(const LinkedList* const linkedList);
