#pragma once

#include <stdbool.h>

typedef enum
{
    cyclicListDefaultErrorCode,
    cyclicListMemoryLack,
    cyclicListNullPointer,
    cyclicListIsEmpty
} CyclicListErrorCode;

typedef struct CyclicList CyclicList;

typedef struct CyclicListElement CyclicListElement;

CyclicList* createCyclicList(void);

void deleteCyclicList(CyclicList** const cyclicList);

CyclicListErrorCode push(CyclicList* const cyclicList, const int value);

CyclicListErrorCode removeNext(CyclicList** const cyclicList, CyclicListElement* const cyclicListElement);

CyclicListErrorCode getNext(CyclicList* const cyclicList, CyclicListElement** const cyclicListElement);

CyclicListErrorCode getCyclicListElementValue(const CyclicListElement* const cyclicListElement, int* const value);

bool isEmpty(const CyclicList* const cyclicList);
