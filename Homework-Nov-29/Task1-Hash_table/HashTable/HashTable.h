#pragma once

#include <stdlib.h>

typedef enum
{
    defaultHashTableErrorCode,
    memoryLackHashTableErrorCode
} HashTableErrorCode;

typedef struct HashTable HashTable;

HashTable* createHashTable(const size_t size);

HashTableErrorCode addWord(const HashTable* const hashTable, const char* const word);

size_t getWordCount(const HashTable* const hashTable, const char* const word);

void deleteHashTable(HashTable** const hashTable);

void printHashTable(const HashTable* const hashTable);

void printAnalysisData(const HashTable* const hashTable);
