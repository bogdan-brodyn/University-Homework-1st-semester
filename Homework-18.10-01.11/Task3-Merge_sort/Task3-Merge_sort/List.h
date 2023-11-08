#pragma once

#include <stdbool.h>

typedef enum
{
    listDefaultErrorCode,
    listMemoryLack,
    listNullPointer
} ListErrorCode;


typedef struct ListElement ListElement;

ListElement* createListElement(char* const name, const unsigned long long phoneNumber);

ListElement* getCopy(const ListElement* const listElement);

void deleteListElement(ListElement* listElement);

ListElement* getNext(const ListElement* const listElement);

ListErrorCode getName(const ListElement* const listElement, char** const name);

ListErrorCode getPhoneNumber(
    const ListElement* const listElement, unsigned long long* const phoneNumber);


typedef struct List List;

bool isEmpty(const List* const list);

ListElement* getFront(const List* const list);

ListErrorCode pushBack(List** const list, ListElement* const listElement);

void popFront(List* const list);

void deleteList(List** const list);
