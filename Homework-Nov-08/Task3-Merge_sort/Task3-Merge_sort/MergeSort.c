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

static List* merge(List** leftList, List** rightList, 
    const Compare compare, ListErrorCode* errorCode)
{
    if (*errorCode != defaultErrorCode)
    {
        deleteList(leftList);
        deleteList(rightList);
        return NULL;
    }
    List* mergeList = NULL;
    while (!isEmpty(*leftList) && !isEmpty(*rightList))
    {
        *errorCode = passFront(&mergeList,
            compare(getFront(*leftList), getFront(*rightList)) <= 0 ? leftList : rightList);
        if (*errorCode != defaultErrorCode)
        {
            deleteList(&mergeList);
            deleteList(leftList);
            deleteList(rightList);
            return NULL;
        }
    }
    concatenateLists(&mergeList, leftList);
    concatenateLists(&mergeList, rightList);
    return mergeList;
}

static List* mergeSortRecursive(List** const list, 
    const size_t sortAreaSize, const Compare compare, ListErrorCode* errorCode)
{
    if (*errorCode != defaultErrorCode)
    {
        return;
    }
    if (sortAreaSize == 1)
    {
        List* newList = NULL;
        *errorCode = passFront(&newList, list);
        return newList;
    }
    const size_t leftPartSize = sortAreaSize / 2;
    List* leftList = mergeSortRecursive(list, leftPartSize, compare, errorCode);
    List* rightList = mergeSortRecursive(list, sortAreaSize - leftPartSize, compare, errorCode);
    return merge(&leftList, &rightList, compare, errorCode);
}

bool mergeSort(List** const list, const Compare compare)
{
    size_t arraySize = 1;
    ListElement* listBackElement = getFront(*list);
    for (; getNext(listBackElement) != NULL; 
        listBackElement = getNext(listBackElement), ++arraySize);
    ListErrorCode* errorCode = defaultErrorCode;
    List* sortedList = mergeSortRecursive(list, arraySize, compare, &errorCode);
    if (errorCode == defaultErrorCode)
    {
        *list = sortedList;
        return true;
    }
    return false;
}
