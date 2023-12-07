#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Dictionary.h"
#include "String.h"

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
    return compare(value, correctValue) == 0 ? testPassed : testFailed;
}

static TestResult test1(void)
{
    Dictionary* dictionary = NULL;
    bool testResult =
        add(&dictionary, "1a3", "a") == dictionaryDefaultErrorCode
        && add(&dictionary, "1b1", "b") == dictionaryDefaultErrorCode
        && add(&dictionary, "acd", "c") == dictionaryDefaultErrorCode
        && add(&dictionary, "abcdf", "d") == dictionaryDefaultErrorCode
        && getAndCompareValue(dictionary, "1a3", "a") == testPassed
        && getAndCompareValue(dictionary, "1b1", "b") == testPassed
        && getAndCompareValue(dictionary, "acd", "c") == testPassed
        && getAndCompareValue(dictionary, "abcdf", "d") == testPassed
        && add(&dictionary, "acd", "e") == dictionaryDefaultErrorCode
        && getAndCompareValue(dictionary, "acd", "e") == testPassed;
    removeKey(dictionary, "acd");
    testResult &=
        getAndCompareValue(dictionary, "1a3", "a") == testPassed
        && getAndCompareValue(dictionary, "1b1", "b") == testPassed
        && getAndCompareValue(dictionary, "abcdf", "d") == testPassed;
    removeKey(dictionary, "1b1");
    testResult &=
        getAndCompareValue(dictionary, "1a3", "a") == testPassed
        && getAndCompareValue(dictionary, "abcdf", "d") == testPassed;
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
    for (size_t i = 0; i < 1e5; ++i)
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
    for (size_t i = 0; i < 1e5; ++i)
    {
        char tempKey[6] = "12345";
        for (char j = 0; j < 5; ++j)
        {
            tempKey[j] = (char)rand();
        }
        removeKey(dictionary, tempKey);
    }
    bool balance = checkBalance(dictionary);
    size_t height = getSearchTreeHeight(dictionary);
    deleteDictionary(&dictionary);
    return balance && height <= 50 ? testPassed : testFailed;
}

TestResult printTestResult(TestResult(*testFunction)(void), const char* const testName)
{
    TestResult testResult = testFunction();
    printf(testResult == testPassed ? "Program has passed the %s test\n" :
        "Program has failed the %s test\n", testName);
    return testResult;
}

int main(void)
{
    return printTestResult(test1, "first") == testPassed
        && printTestResult(test2, "second") == testPassed
        && printTestResult(test3, "third") == testPassed ? testPassed : testFailed;
}
