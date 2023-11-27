#include <stdio.h>
#include <stdbool.h>
#include <time.h>

#include "HashTable.h"

bool test(void)
{
    const size_t hashTableSize = 10;
    HashTable* hashTable = createHashTable(hashTableSize);
    bool isPassed =
        hashTable != NULL
        && addWord(hashTable, "ab1c") == defaultHashTableErrorCode
        && addWord(hashTable, "abc") == defaultHashTableErrorCode
        && addWord(hashTable, "gb3") == defaultHashTableErrorCode
        && addWord(hashTable, "abc") == defaultHashTableErrorCode
        && addWord(hashTable, "ab1cd") == defaultHashTableErrorCode
        && addWord(hashTable, "abc") == defaultHashTableErrorCode
        && addWord(hashTable, "ab1c") == defaultHashTableErrorCode
        && getWordCount(hashTable, "gb3") == 1
        && getWordCount(hashTable, "ab1c") == 2
        && getWordCount(hashTable, "ab1cd") == 1
        && getWordCount(hashTable, "abc") == 3;
    deleteHashTable(&hashTable);
    return isPassed && hashTable == NULL;
}

bool loadTest(void)
{
    srand(time(NULL));
    clock_t start = clock();
    const size_t hashTableSize = (size_t)1e5;
    HashTable* hashTable = createHashTable(hashTableSize);
    for (size_t i = 0; i < hashTableSize; ++i)
    {
        char randomWord[] = "12345";
        for (char i = 0; i < 5; ++i)
        {
            randomWord[i] = (char)rand();
        }
        HashTableErrorCode errorCode = addWord(hashTable, randomWord);
        if (errorCode != defaultHashTableErrorCode)
        {
            deleteHashTable(&hashTable);
            return false;
        }
    }
    clock_t end = clock();
    printf("Load test execution time: %f\n", (float)(end - start) / CLOCKS_PER_SEC);
    printAnalysisData(hashTable);
    deleteHashTable(&hashTable);
    return true;
}

int main(void)
{
    bool isTestPassed = test();
    printf(isTestPassed ? "Program has passed the test\n" : "Program has failed the test\n");
    bool isLoadTestPassed = loadTest();
    return !isTestPassed && !isLoadTestPassed;
}
