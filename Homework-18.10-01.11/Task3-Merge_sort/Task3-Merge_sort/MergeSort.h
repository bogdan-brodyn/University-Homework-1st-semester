#pragma once

#include <stdlib.h>

#include "List.h"

typedef int (*Compare)(const ListElement* const, const ListElement* const);

int compareByName(const ListElement* const listElement1,
    const ListElement* const listElement2);

int compareByPhoneNumber(const ListElement* const listElement1,
    const ListElement* const listElement2);

void mergeSort(List** const list, Compare compare);
