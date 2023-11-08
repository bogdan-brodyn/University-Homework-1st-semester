#include <stdlib.h>

#include "MergeSort.h"

static void glueLists(List* destination, List* source)
{
    ListElement* sourcePointer = getFront(source);
    while (!isEmpty(source))
    {
        pushBack(&destination, getCopy(sourcePointer));
        sourcePointer = getNext(sourcePointer);
        popFront(source);
    }
}

static List* merge(List* leftList, List* rightList, Compare compare)
{
    List* mergeList = NULL;
    ListElement* leftPointer = getFront(leftList);
    ListElement* rightPointer = getFront(rightList);
    while (!isEmpty(leftList) && !isEmpty(rightList))
    {
        ListElement* minListElement = NULL;
        if (compare(leftPointer, rightPointer) <= 0)
        {
            minListElement = getCopy(leftPointer);
            leftPointer = getNext(leftPointer);
            popFront(leftList);
        }
        else
        {
            minListElement = getCopy(rightPointer);
            rightPointer = getNext(rightPointer);
            popFront(rightList);
        }
        pushBack(&mergeList, minListElement);
    }
    glueLists(mergeList, leftList);
    glueLists(mergeList, rightList);
    deleteList(&leftList);
    deleteList(&rightList);
    return mergeList;
}

static List* mergeSortRecursive(const List* const list, const size_t const sortAreaSize,
    const ListElement* const leftBorder, const ListElement* const rightBorder, Compare compare)
{
    if (sortAreaSize == 1)
    {
        List* list = NULL;
        pushBack(&list, getCopy(leftBorder));
        return list;
    }
    size_t middle = sortAreaSize / 2;
    ListElement* middleElement = leftBorder;
    for (size_t i = 1; i < middle; middleElement = getNext(middleElement), ++i);
    List* leftList = mergeSortRecursive(
        list, middle, leftBorder, middleElement, compare);
    List* rightList = mergeSortRecursive(
        list, sortAreaSize - middle, getNext(middleElement), rightBorder, compare);
    return merge(leftList, rightList, compare);
}

List* mergeSort(const List* const list, Compare compare)
{
    size_t arraySize = 1;
    ListElement* temp = getFront(list);
    for (; getNext(temp) != NULL; temp = getNext(temp), ++arraySize);
    return mergeSortRecursive(list, arraySize, getFront(list), temp, compare);
}
