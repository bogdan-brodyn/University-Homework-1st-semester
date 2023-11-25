#include <stdlib.h>

#include "HashTable.h"
#include "LinkedList.h"

#define HASH_TABLE_SIZE 514229

struct HashTable
{
    LinkedList** array;
};

static size_t getStringHash(const char* const string)
{
    size_t hash = 0;
    size_t alphabetSize = CHAR_MAX - CHAR_MIN + 1;
    for (size_t i = 0; string[i] != '\0'; ++i)
    {
        hash = (hash * alphabetSize
            + ((size_t)string[i] - CHAR_MIN + 1)) % HASH_TABLE_SIZE;
    }
    return hash;
}

HashTableErrorCode addWord(HashTable** const hashTable, const char* const word)
{
    if (*hashTable == NULL)
    {
        *hashTable = (HashTable*)calloc(1, sizeof(HashTable));
        if (*hashTable == NULL)
        {
            return memoryLackHashTableErrorCode;
        }
        (*hashTable)->array = (LinkedList**)calloc(HASH_TABLE_SIZE, sizeof(LinkedList*));
        if ((*hashTable)->array == NULL)
        {
            free(*hashTable);
            return memoryLackHashTableErrorCode;
        }
    }
    size_t wordHash = getStringHash(word);
    LinkedListErrorCode errorCode = pushString(&((*hashTable)->array[wordHash]), word);
    if (errorCode == memoryLackLinkedListErrorCode)
    {
        return memoryLackHashTableErrorCode;
    }
    return defaultHashTableErrorCode;
}

size_t getWordCount(const HashTable* const hashTable, const char* const word)
{
    size_t wordHash = getStringHash(word);
    return getElementCount(hashTable->array[wordHash], word);
}

void deleteHashTable(HashTable** const hashTable)
{
    if (hashTable == NULL || *hashTable == NULL)
    {
        return;
    }
    for (size_t i = 0; i < HASH_TABLE_SIZE; ++i)
    {
        deleteLinkedList(&((*hashTable)->array[i]));
    }
    free((*hashTable)->array);
    free((*hashTable));
    *hashTable = NULL;
}

void printHashTable(const HashTable* const hashTable)
{
    for (size_t i = 0; i < HASH_TABLE_SIZE; ++i)
    {
        if (hashTable->array[i] != NULL)
        {
            printLinkedList(hashTable->array[i]);
        }
    }
}

void printAnalysisData(const HashTable* const hashTable)
{
    size_t filledTableElementsCount = 0;
    size_t wordsCount = 0;
    size_t maxListLength = 0;
    for (size_t i = 0; i < HASH_TABLE_SIZE; ++i)
    {
        if (hashTable->array[i] != NULL)
        {
            ++filledTableElementsCount;
            size_t listLength = getLength(hashTable->array[i]);
            wordsCount += listLength;
            maxListLength = max(maxListLength, listLength);
        }
    }
    printf("Коэффциент заполнения: %f\n", (float)filledTableElementsCount / HASH_TABLE_SIZE);
    printf("максимальную и среднюю длину списка в сегменте таблицы соответственно %lld и %f\n",
        maxListLength, (float)wordsCount / filledTableElementsCount);
}
