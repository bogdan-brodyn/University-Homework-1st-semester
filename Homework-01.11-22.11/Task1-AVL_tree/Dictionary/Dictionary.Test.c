#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Dictionary.h"

typedef enum
{
    testPassed,
    testFailed
} TestResult;

static TestResult getAndCompareValue(const Dictionary* const dictionary, 
    const char* const key, const char* const correctValue)
{
    char* value = NULL;
    int errorCode = get(dictionary, key, &value);
    if (errorCode != dictionaryDefaultErrorCode)
    {
        return testFailed;
    }
    for (size_t i = 0; correctValue[i] != '\0' || value[i] != '\0'; ++i)
    {
        if (correctValue[i] != value[i])
        {
            return testFailed;
        }
    }
    return testPassed;
}

static TestResult test1(void)
{
    Dictionary* dictionary = NULL;
    bool testResult =
        add(&dictionary, "2", "b") == dictionaryDefaultErrorCode
        && add(&dictionary, "1", "a") == dictionaryDefaultErrorCode
        && add(&dictionary, "3", "c") == dictionaryDefaultErrorCode
        && add(&dictionary, "4", "d") == dictionaryDefaultErrorCode
        && getAndCompareValue(dictionary, "1", "a") == testPassed
        && getAndCompareValue(dictionary, "2", "b") == testPassed
        && getAndCompareValue(dictionary, "3", "c") == testPassed
        && getAndCompareValue(dictionary, "4", "d") == testPassed
        && add(&dictionary, "3", "e") == dictionaryDefaultErrorCode
        && getAndCompareValue(dictionary, "3", "e") == testPassed;
    removeKey(dictionary, "3");
    testResult &=
        getAndCompareValue(dictionary, "1", "a") == testPassed
        && getAndCompareValue(dictionary, "2", "b") == testPassed
        && getAndCompareValue(dictionary, "4", "d") == testPassed;
    removeKey(dictionary, "2");
    testResult &=
        getAndCompareValue(dictionary, "1", "a") == testPassed
        && getAndCompareValue(dictionary, "4", "d") == testPassed;
    deleteDictionary(&dictionary);
    return testResult && dictionary == NULL ? testPassed : testFailed;
}

static TestResult test2(void)
{
    Dictionary* dictionary = NULL;
    char* value = NULL;
    bool testResult =
        add(NULL, "1", "a") == dictionaryNullPointer
        && get(NULL, "1", &value) == dictionaryNullPointer
        && get(dictionary, "1", NULL) == dictionaryNullPointer;
    testResult &= add(&dictionary, "1", "a") == dictionaryDefaultErrorCode;
    testResult &= get(dictionary, "2", &value) == dictionaryNonExistentKey;
    deleteDictionary(&dictionary);
    return testResult && dictionary == NULL ? testPassed : testFailed;
}

static TestResult test3(void)
{
    srand((unsigned int)time(NULL));
    Dictionary* dictionary = NULL;
    for (size_t i = 0; i < (size_t)1e5; ++i)
    {
        char tempKey[6] = "12345";
        char tempValue[6] = "12345";
        for (char j = 0; j < 5; ++j)
        {
            tempKey[j] = (char)rand();
            tempValue[j] = (char)rand();
        }
        add(&dictionary, tempKey, tempValue);
    }
    bool balance = checkBalance(dictionary);
    size_t height = getSearchTreeHeight(dictionary);
    deleteDictionary(&dictionary);
    return balance && height <= 50;
}

int main(void)
{
    TestResult test1Result = test1();
    printf(test1Result == testPassed ? "Program has passed the first test\n" : 
        "Program has failed the first test\n");
    TestResult test2Result = test2();
    printf(test2Result == testPassed ? "Program has passed the second test\n" :
        "Program has failed the second test\n");
    TestResult test3Result = test3();
    printf(test2Result == testPassed ? "Program has passed the third test\n" :
        "Program has failed the third test\n");
    return test1Result == testPassed 
        && test2Result == testPassed
        && test3Result == testPassed ? testPassed : testFailed;
}
