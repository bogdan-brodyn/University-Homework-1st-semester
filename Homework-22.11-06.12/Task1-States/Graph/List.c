#include <stdlib.h>

#include "List.h"

struct List
{
    size_t size;
    size_t capasity;
    ListValue* array;
};

size_t getSize(const List* const list)
{
    return list->size;
}

static List* createList(void)
{
    List* list = (List*)malloc(sizeof(List));
    if (list == NULL)
    {
        return NULL;
    }
    list->size = 0;
    list->capasity = 1;
    list->array = (ListValue*)malloc(sizeof(ListValue));
    if (list->array == NULL)
    {
        free(list);
        return NULL;
    }
    return list;
}

ListErrorCode pushBack(List** const list, const ListValue value)
{
    if (*list == NULL)
    {
        *list = createList();
        if (*list == NULL)
        {
            return memoryLackListErrorCode;
        }
    }

    if ((*list)->size >= (*list)->capasity)
    {
        ListValue* temp = (ListValue*)realloc((*list)->array,
            2 * (*list)->capasity * sizeof(ListValue));
        if (temp == NULL)
        {
            return memoryLackListErrorCode;
        }
        (*list)->array = temp;
        (*list)->capasity *= 2;
    }
    (*list)->array[(*list)->size++] = value;
    return defaultListErrorCode;
}

ListValue get(const List* const list, const size_t index)
{
    return list->array[index];
}

void deleteList(List** const list)
{
    if (list == NULL || *list == NULL)
    {
        return;
    }
    free((*list)->array);
    free(*list);
    *list = NULL;
}
