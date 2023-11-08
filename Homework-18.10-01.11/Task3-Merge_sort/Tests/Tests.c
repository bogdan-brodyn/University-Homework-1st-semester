#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "../Task3-Merge_sort/List.h"
#include "../Task3-Merge_sort/MergeSort.h"

typedef enum
{
    testPassed,
    testFailed
} TestResult;

static TestResult getValueAndCompare(const ListElement* const listElement, 
    const char* const name, const unsigned long long phoneNumber)
{
    char* elementName = NULL;
    unsigned long long elementPhoneNumber = 0;
    const ListErrorCode errorCode1 = getName(listElement, &elementName);
    const ListErrorCode errorCode2 = getPhoneNumber(listElement, &elementPhoneNumber);
    bool AreNamesSame = true;
    for (size_t i = 0; ; ++i)
    {
        if (name[i] != elementName[i])
        {
            AreNamesSame = false;
            break;
        }
        if (name[i] == '\0' || elementName[i] == '\0')
        {
            break;
        }
    }
    return errorCode1 == listDefaultErrorCode && errorCode2 == listDefaultErrorCode 
        && phoneNumber == elementPhoneNumber && AreNamesSame ? testPassed : testFailed;
}

static TestResult testList(void)
{
    List* list = NULL;
    bool isTestPassed =
        pushBack(&list, createListElement("aa", 11)) == listDefaultErrorCode
        && list != NULL
        && pushBack(&list, createListElement("bb", 22)) == listDefaultErrorCode
        && pushBack(&list, createListElement("cc", 33)) == listDefaultErrorCode;
    isTestPassed &=
        getValueAndCompare(getFront(list), "aa", 11) == testPassed
        && getValueAndCompare(getNext(getFront(list)), "bb", 22) == testPassed
        && getValueAndCompare(getNext(getNext(getFront(list))), "cc", 33) == testPassed;
    popFront(list);
    isTestPassed &=
        getValueAndCompare(getFront(list), "bb", 22) == testPassed
        && getValueAndCompare(getNext(getFront(list)), "cc", 33) == testPassed;
    popFront(list);
    isTestPassed &=
        getValueAndCompare(getFront(list), "cc", 33) == testPassed;
    deleteList(&list);
    return isTestPassed && list == NULL ? testPassed : testFailed;
}

static TestResult testMergeSort(void)
{
    srand((unsigned int)time(NULL));
    List* randomList = NULL;
    const size_t randomListSize = (size_t)1e5;
    for (size_t i = 0; i < randomListSize; ++i)
    {
        ListElement* newListElement = createListElement(NULL, rand());
        pushBack(&randomList, newListElement);
    }
    List* sortedList = mergeSort(randomList, compareByPhoneNumber);
    ListElement* prev = getFront(sortedList);
    ListElement* cur = getNext(prev);
    TestResult testResult = testPassed;
    for (; cur != NULL; prev = cur, cur = getNext(cur))
    {
        if (compareByPhoneNumber(prev, cur) > 0)
        {
            testResult = testFailed;
            break;
        }
    }
    deleteList(&randomList);
    deleteList(&sortedList);
    return testResult;
}

int main(void)
{
    printf(testList() == testPassed ? "Program has passed the first test\n" :
        "Program has failed the first test\n");
    printf(testMergeSort() == testPassed ? "Program has passed the second test\n" :
        "Program has failed the second test\n");
}
