#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "List.h"

struct ListElement
{
    char* name;
    unsigned long long phoneNumber;
    ListElement* next;
};

ListElement* createListElement(const char* const name, 
    const unsigned long long phoneNumber)
{
    ListElement* listElement = (ListElement*)calloc(1, sizeof(ListElement));
    if (listElement == NULL)
    {
        return NULL;
    }
    if (name != NULL)
    { 
        const size_t nameSize = strlen(name) + 1;
        listElement->name = (char*)malloc(nameSize * sizeof(char));
        if (listElement->name == NULL)
        {
            free(listElement);
            return NULL;
        }
        strcpy_s(listElement->name, nameSize * sizeof(char), name);
    }
    listElement->phoneNumber = phoneNumber;
    return listElement;
}

void deleteListElement(ListElement* listElement)
{
    if (listElement == NULL)
    {
        return;
    }
    free(listElement->name);
    free(listElement);
}

ListElement* getNext(const ListElement* const listElement)
{
    return listElement->next;
}

char* getName(const ListElement* const listElement)
{
    return listElement->name;
}

unsigned long long getPhoneNumber(const ListElement* const listElement)
{
    return listElement->phoneNumber;
}


struct List
{
    ListElement* front;
    ListElement* back;
};

bool isEmpty(const List* const list)
{
    return list == NULL || list->front == NULL && list->back == NULL;
}

ListElement* getFront(const List* const list)
{
    return list->front;
}

ListErrorCode passFront(List** destination, List** source)
{
    ListElement* passingListElement = (*source)->front;
    (*source)->front = passingListElement->next;
    if ((*source)->front == NULL)
    {
        (*source)->back = NULL;
        deleteList(source);
    }
    passingListElement->next = NULL;
    return pushBack(destination, passingListElement);
}

void popFront(List* const list)
{
    if (isEmpty(list))
    {
        return;
    }
    ListElement* frontListElement = getFront(list);
    list->front = frontListElement->next;
    list->back = list->front == NULL ? NULL : list->back;
    deleteListElement(frontListElement);
}

ListErrorCode pushBack(List** const list, ListElement* const listElement)
{
    if (*list == NULL)
    {
        *list = (List*)calloc(1, sizeof(List));
        if (*list == NULL)
        {
            return listMemoryLack;
        }
    }
    if (isEmpty(*list))
    {
        (*list)->front = listElement;
    }
    else
    {
        (*list)->back->next = listElement;
    }
    (*list)->back = listElement;
    return listDefaultErrorCode;
}

void concatenateLists(List** destination, List** source)
{
    if (isEmpty(*source))
    {
        return;
    }
    if (isEmpty(*destination))
    {
        passFront(destination, source);
    }
    if (!isEmpty(*source))
    {
        (*destination)->back->next = (*source)->front;
        (*destination)->back = (*source)->back;
    }
    (*source)->front = NULL;
    (*source)->back = NULL;
    deleteList(source);
}

void deleteList(List** const list)
{
    if (list == NULL)
    {
        return;
    }
    while (!isEmpty(*list))
    {
        popFront(*list);
    }
    free(*list);
    *list = NULL;
}

void printList(const List* const list)
{
    for (ListElement* i = list->front; i != NULL; i = getNext(i))
    {
        printf("%s - %lld\n", i->name, i->phoneNumber);
    }
}
