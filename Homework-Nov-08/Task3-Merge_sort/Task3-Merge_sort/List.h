#pragma once

#include <stdbool.h>

typedef enum
{
    listDefaultErrorCode,
    listMemoryLack,
    listNullPointer
} ListErrorCode;


typedef struct ListElement ListElement;

ListElement* createListElement(const char* const name,
    const unsigned long long phoneNumber);

void deleteListElement(ListElement* listElement);

ListElement* getNext(const ListElement* const listElement);

char* getName(const ListElement* const listElement);

unsigned long long getPhoneNumber(const ListElement* const listElement);


typedef struct List List;

bool isEmpty(const List* const list);

ListElement* getFront(const List* const list);

ListErrorCode passFront(List** destination, List** source);

void popFront(List* const list);

ListErrorCode pushBack(List** const list, ListElement* const listElement);

ListErrorCode concatenateLists(List** destination, List** source);

void deleteList(List** const list);

void printList(const List* const list);
