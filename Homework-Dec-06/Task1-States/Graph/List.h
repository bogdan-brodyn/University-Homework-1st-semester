#pragma once

#include <stdlib.h>

typedef enum
{
    defaultListErrorCode,
    memoryLackListErrorCode
} ListErrorCode;

typedef size_t ListValue;

typedef struct List List;

size_t getSize(const List* const list);

ListErrorCode pushBack(List** const list, const ListValue value);

ListValue get(const List* const list, const size_t index);

void deleteList(List** const list);
