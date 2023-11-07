#include <stdio.h>
#include <stdlib.h>

#include "Dictionary.h"

typedef enum
{
    testPassed,
    testFailed
} TestResult;

static TestResult getAndCompareValue(const Dictionary* const dictionary, 
    const int key, const char* const correctValue)
{
    char* value = NULL;
    int errorCode = get(dictionary, key, &value);
    if (errorCode != dictionaryDefaultErrorCode)
    {
        return testFailed;
    }
    for (size_t i = 0; ; ++i)
    {
        if (correctValue[i] == '\0' || value[i] == '\0')
        {
            return correctValue[i] == value[i] ? testPassed : testFailed;
        }
        if (correctValue[i] != value[i])
        {
            return testFailed;
        }
    }
    return testFailed;
}

static TestResult test1(void)
{
    Dictionary* dictionary = NULL;
    bool testResult =
        add(&dictionary, 2, "b") == dictionaryDefaultErrorCode
        && add(&dictionary, 1, "a") == dictionaryDefaultErrorCode
        && add(&dictionary, 3, "c") == dictionaryDefaultErrorCode
        && add(&dictionary, 4, "d") == dictionaryDefaultErrorCode
        && getAndCompareValue(dictionary, 1, "a") == testPassed
        && getAndCompareValue(dictionary, 2, "b") == testPassed
        && getAndCompareValue(dictionary, 3, "c") == testPassed
        && getAndCompareValue(dictionary, 4, "d") == testPassed
        && add(&dictionary, 3, "e") == dictionaryDefaultErrorCode
        && getAndCompareValue(dictionary, 3, "e") == testPassed;
    removeKey(dictionary, 3);
    testResult &=
        getAndCompareValue(dictionary, 1, "a") == testPassed
        && getAndCompareValue(dictionary, 2, "b") == testPassed
        && getAndCompareValue(dictionary, 4, "d") == testPassed;
    removeKey(dictionary, 2);
    testResult &=
        getAndCompareValue(dictionary, 1, "a") == testPassed
        && getAndCompareValue(dictionary, 4, "d") == testPassed;
    deleteDictionary(&dictionary);
    return testResult && dictionary == NULL ? testPassed : testFailed;
}

static TestResult test2(void)
{
    Dictionary* dictionary = NULL;
    char* value = NULL;
    bool testResult =
        add(NULL, 1, "a") == dictionaryNullPointer
        && get(NULL, 1, &value) == dictionaryNullPointer
        && get(dictionary, 1, NULL) == dictionaryNullPointer;
    testResult &= add(&dictionary, 1, "a") == dictionaryDefaultErrorCode;
    testResult &= get(dictionary, 2, &value) == dictionaryNonExistentKey;
    deleteDictionary(&dictionary);
    return testResult && dictionary == NULL ? testPassed : testFailed;
}

int main(void)
{
    TestResult test1Result = test1();
    printf(test1Result == testPassed ? "Program has passed the first test\n" : 
        "Program has failed the first test\n");
    TestResult test2Result = test2();
    printf(test2Result == testPassed ? "Program has passed the second test\n" :
        "Program has failed the second test\n");
    return test1Result == testPassed 
        && test2Result == testPassed ? testPassed : testFailed;
}
