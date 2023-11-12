#include <stdlib.h>

#include "MergeSort.h"

int compareByName(const ListElement* const listElement1,
    const ListElement* const listElement2)
{
    char* name1 = getName(listElement1);
    char* name2 = getName(listElement2);
    for (size_t i = 0; name1[i] != '\0' || name2[i] != '\0'; ++i)
    {
        if (name1[i] != name2[i])
        {
            return name1[i] - name2[i];
        }
    }
    return 0;
}

int compareByPhoneNumber(const ListElement* const listElement1,
    const ListElement* const listElement2)
{
    return getPhoneNumber(listElement1) - getPhoneNumber(listElement2);
}

static List* merge(List** leftList, List** rightList, const Compare compare)
{
    List* mergeList = NULL;
    while (!isEmpty(*leftList) && !isEmpty(*rightList))
    {
        passFront(&mergeList, 
            compare(getFront(*leftList), getFront(*rightList)) <= 0 ? leftList : rightList);
    }
    concatenateLists(&mergeList, leftList);
    concatenateLists(&mergeList, rightList);
    return mergeList;
}

static List* mergeSortRecursive(List** const list, 
    const size_t sortAreaSize, const Compare compare)
{
    if (sortAreaSize == 1)
    {
        List* newList = NULL;
        passFront(&newList, list);
        return newList;
    }
    size_t leftPartSize = sortAreaSize / 2;
    List* leftList = mergeSortRecursive(list, leftPartSize, compare);
    List* rightList = mergeSortRecursive(list, sortAreaSize - leftPartSize, compare);
    return merge(&leftList, &rightList, compare);
}

void mergeSort(List** const list, const Compare compare)
{
    size_t arraySize = 1;
    ListElement* listBackElement = getFront(*list);
    for (; getNext(listBackElement) != NULL; 
        listBackElement = getNext(listBackElement), ++arraySize);
    *list = mergeSortRecursive(list, arraySize, compare);
}
