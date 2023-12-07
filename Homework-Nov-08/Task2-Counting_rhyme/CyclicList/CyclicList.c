#include <stdlib.h>

#include "CyclicList.h"

struct CyclicListElement
{
    int value;
    CyclicListElement* next;
};

struct CyclicList
{
    CyclicListElement* tail;
};

CyclicList* createCyclicList(void)
{
    return (CyclicList*)calloc(1, sizeof(CyclicList));
}

void deleteCyclicList(CyclicList** const cyclicList)
{
    if (cyclicList == NULL)
    {
        return;
    }
    while (!isEmpty(*cyclicList))
    {
        removeNext(cyclicList, (*cyclicList)->tail);
    }
    free(*cyclicList);
    *cyclicList = NULL;
}

CyclicListErrorCode push(CyclicList* const cyclicList, const int value)
{
    if (cyclicList == NULL)
    {
        return cyclicListNullPointer;
    }
    CyclicListElement* const newCyclicListElement = (CyclicListElement* const)malloc(sizeof(CyclicListElement));
    if (newCyclicListElement == NULL)
    {
        return cyclicListMemoryLack;
    }
    newCyclicListElement->value = value;
    if (isEmpty(cyclicList))
    {
        newCyclicListElement->next = newCyclicListElement;
    }
    else
    {
        newCyclicListElement->next = cyclicList->tail->next;
        cyclicList->tail->next = newCyclicListElement;
    }
    cyclicList->tail = newCyclicListElement;
    return cyclicListDefaultErrorCode;
}

CyclicListErrorCode removeNext(CyclicList** const cyclicList, CyclicListElement* const cyclicListElement)
{
    if (cyclicList == NULL || cyclicListElement == NULL)
    {
        return cyclicListNullPointer;
    }
    if (*cyclicList == NULL)
    {
        return cyclicListDefaultErrorCode;
    }
    if ((*cyclicList)->tail == cyclicListElement->next)
    {
        (*cyclicList)->tail = cyclicListElement == cyclicListElement->next ? NULL : cyclicListElement;
    }
    CyclicListElement* const temp = cyclicListElement->next;
    cyclicListElement->next = cyclicListElement->next->next;
    free(temp);
    return cyclicListDefaultErrorCode;
}

CyclicListErrorCode getNext(CyclicList* const cyclicList, CyclicListElement** const cyclicListElement)
{
    if (cyclicList == NULL || cyclicListElement == NULL)
    {
        return cyclicListNullPointer;
    }
    if (isEmpty(cyclicList))
    {
        return cyclicListIsEmpty;
    }
    *cyclicListElement = *cyclicListElement == NULL ? cyclicList->tail : (*cyclicListElement)->next;
    return cyclicListDefaultErrorCode;
}

CyclicListErrorCode getCyclicListElementValue(const CyclicListElement* const cyclicListElement, int* const value)
{
    if (cyclicListElement == NULL || value == NULL)
    {
        return cyclicListNullPointer;
    }
    *value = cyclicListElement->value;
    return cyclicListDefaultErrorCode;
}

bool isEmpty(const CyclicList* const cyclicList)
{
    return cyclicList == NULL || cyclicList->tail == NULL;
}
