#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "../Task3-Merge_sort/List.h"
#include "../Task3-Merge_sort/MergeSort.h"

#define DEFAULT_ERROR_CODE 0
#define TEST_FAILED 1

static bool getValueAndCompare(const ListElement* const listElement, 
    const char* const name, const unsigned long long phoneNumber)
{
    ListElement* temp = createListElement(name, phoneNumber);
    if (temp == NULL || listElement == NULL)
    {
        return false;
    }
    int compareByNameResult = compareByName(listElement, temp);
    unsigned long long compareByPhoneNumberResult = compareByPhoneNumber(listElement, temp);
    deleteListElement(temp);
    return compareByNameResult == 0 && compareByPhoneNumberResult == 0;
}

static bool testList(void)
{
    List* list = NULL;
    bool isTestPassed =
        pushBack(&list, createListElement("aa", 11)) == listDefaultErrorCode
        && list != NULL
        && pushBack(&list, createListElement("bb", 22)) == listDefaultErrorCode
        && pushBack(&list, createListElement("cc", 33)) == listDefaultErrorCode
        && getValueAndCompare(getFront(list), "aa", 11)
        && getValueAndCompare(getNext(getFront(list)), "bb", 22)
        && getValueAndCompare(getNext(getNext(getFront(list))), "cc", 33);
    popFront(list);
    isTestPassed &=
        getValueAndCompare(getFront(list), "bb", 22)
        && getValueAndCompare(getNext(getFront(list)), "cc", 33);
    popFront(list);
    isTestPassed &=
        getValueAndCompare(getFront(list), "cc", 33);
    deleteList(&list);
    return isTestPassed && list == NULL;
}

static bool testMergeSort(void)
{
    srand((unsigned int)time(NULL));
    List* randomList = NULL;
    const size_t randomListSize = (size_t)1e5;
    for (size_t i = 0; i < randomListSize; ++i)
    {
        ListErrorCode errorCode = pushBack(&randomList, createListElement(NULL, rand()));
        if (errorCode != listDefaultErrorCode)
        {
            deleteList(&randomList);
            return false;
        }
    }
    if (!mergeSort(&randomList, compareByPhoneNumber))
    {
        return false;
    }
    ListElement* prev = getFront(randomList);
    ListElement* cur = getNext(prev);
    bool testResult = true;
    for (; cur != NULL; prev = cur, cur = getNext(cur))
    {
        if (compareByPhoneNumber(prev, cur) > 0)
        {
            testResult = false;
            break;
        }
    }
    deleteList(&randomList);
    return testResult;
}

int main(void)
{
    bool isFirstTestPassed = testList();
    printf(isFirstTestPassed ? "Program has passed the first test\n" :
        "Program has failed the first test\n");
    bool isSecondTestPassed = testMergeSort();
    printf(isSecondTestPassed ? "Program has passed the second test\n" :
        "Program has failed the second test\n");
    return isFirstTestPassed && isSecondTestPassed ? DEFAULT_ERROR_CODE : TEST_FAILED;
}
