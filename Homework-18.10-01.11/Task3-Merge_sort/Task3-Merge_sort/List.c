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

ListElement* createListElement(const char* const name, const unsigned long long phoneNumber)
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

ListElement* getCopy(const ListElement* const listElement)
{
    char* name = NULL;
    unsigned long long phoneNumber = 0;
    getName(listElement, &name);
    getPhoneNumber(listElement, &phoneNumber);
    return createListElement(name, phoneNumber);
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
    return listElement == NULL ? NULL : listElement->next;
}

ListErrorCode getName(const ListElement* const listElement, char** const name)
{
    if (listElement == NULL || name == NULL)
    {
        return listNullPointer;
    }
    *name = listElement->name;
    return listDefaultErrorCode;
}

ListErrorCode getPhoneNumber(
    const ListElement* const listElement, unsigned long long* const phoneNumber)
{
    if (listElement == NULL || phoneNumber == NULL)
    {
        return listNullPointer;
    }
    *phoneNumber = listElement->phoneNumber;
    return listDefaultErrorCode;
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
    return list == NULL ? NULL : list->front;
}

ListErrorCode pushBack(List** const list, ListElement* const listElement)
{
    if (list == NULL || listElement == NULL)
    {
        return listNullPointer;
    }
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

void deleteList(List** const list)
{
    while (!isEmpty(*list))
    {
        popFront(*list);
    }
    free(*list);
    *list = NULL;
}
