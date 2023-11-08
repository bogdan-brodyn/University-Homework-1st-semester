#pragma once

#include <stdlib.h>

#include "List.h"

typedef int (*Compare)(const ListElement* const, const ListElement* const);

inline int compareByName(
    const ListElement* const listElement1, const ListElement* const listElement2)
{
    char* name1 = NULL;
    char* name2 = NULL;
    getName(listElement1, &name1);
    getName(listElement2, &name2);
    size_t i = 0;
    for (; name1[i] != '\0' && name2[i] != '\0'; ++i)
    {
        if (name1[i] != name2[i])
        {
            return name1[i] - name2[i];
        }
    }
    return name1[i] - name2[i];
}

inline int compareByPhoneNumber(
    const ListElement* const listElement1, const ListElement* const listElement2)
{
    unsigned long long phoneNumber1 = 0;
    unsigned long long phoneNumber2 = 0;
    getPhoneNumber(listElement1, &phoneNumber1);
    getPhoneNumber(listElement2, &phoneNumber2);
    return phoneNumber1 - phoneNumber2;
}

List* mergeSort(const List* const list, Compare compare);
