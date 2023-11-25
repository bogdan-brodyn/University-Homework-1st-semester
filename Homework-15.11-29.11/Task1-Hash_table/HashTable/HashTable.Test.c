#include <stdio.h>
#include <stdbool.h>

#include "HashTable.h"

bool test(void)
{
    HashTable* hashTable = NULL;
    bool isPassed =
        addWord(&hashTable, "ab1c") == defaultHashTableErrorCode
        && addWord(&hashTable, "abc") == defaultHashTableErrorCode
        && addWord(&hashTable, "gb3") == defaultHashTableErrorCode
        && addWord(&hashTable, "abc") == defaultHashTableErrorCode
        && addWord(&hashTable, "ab1cd") == defaultHashTableErrorCode
        && addWord(&hashTable, "abc") == defaultHashTableErrorCode
        && addWord(&hashTable, "ab1c") == defaultHashTableErrorCode
        && getWordCount(hashTable, "gb3") == 1
        && getWordCount(hashTable, "ab1c") == 2
        && getWordCount(hashTable, "ab1cd") == 1
        && getWordCount(hashTable, "abc") == 3;
    deleteHashTable(&hashTable);
    return isPassed && hashTable == NULL;
}

int main(void)
{
    bool isTestPassed = test();
    printf(isTestPassed ? "Program has passed the test\n" : "Program has failed the test\n");
    return !isTestPassed;
}
