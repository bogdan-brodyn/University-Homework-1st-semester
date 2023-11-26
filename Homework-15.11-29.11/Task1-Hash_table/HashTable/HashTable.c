#include <stdlib.h>

#include "HashTable.h"
#include "LinkedList.h"

struct HashTable
{
    size_t size;
    LinkedList** array;
};

HashTable* createHashTable(const size_t size)
{
    HashTable* hashTable = (HashTable*)malloc(sizeof(HashTable));
    if (hashTable == NULL)
    {
        return NULL;
    }
    hashTable->size = size;
    hashTable->array = (LinkedList**)calloc(size, sizeof(LinkedList*));
    if (hashTable->array == NULL)
    {
        free(hashTable);
        return NULL;
    }
    return hashTable;
}

static size_t getStringHash(const HashTable* const hashTable, const char* const string)
{
    size_t hash = 0;
    size_t alphabetSize = CHAR_MAX - CHAR_MIN + 1;
    for (size_t i = 0; string[i] != '\0'; ++i)
    {
        hash = (hash * alphabetSize
            + ((size_t)string[i] - CHAR_MIN + 1)) % hashTable->size;
    }
    return hash;
}

HashTableErrorCode addWord(const HashTable* const hashTable, const char* const word)
{
    size_t wordHash = getStringHash(hashTable, word);
    LinkedListErrorCode errorCode = 
        pushString(&(hashTable->array[wordHash]), word);
    if (errorCode == memoryLackLinkedListErrorCode)
    {
        return memoryLackHashTableErrorCode;
    }
    return defaultHashTableErrorCode;
}

size_t getWordCount(const HashTable* const hashTable, const char* const word)
{
    size_t wordHash = getStringHash(hashTable, word);
    return getElementCount(hashTable->array[wordHash], word);
}

void deleteHashTable(HashTable** const hashTable)
{
    if (hashTable == NULL || *hashTable == NULL)
    {
        return;
    }
    for (size_t i = 0; i < (*hashTable)->size; ++i)
    {
        deleteLinkedList(&((*hashTable)->array[i]));
    }
    free((*hashTable)->array);
    free((*hashTable));
    *hashTable = NULL;
}

void printHashTable(const HashTable* const hashTable)
{
    for (size_t i = 0; i < hashTable->size; ++i)
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
    for (size_t i = 0; i < hashTable->size; ++i)
    {
        if (hashTable->array[i] != NULL)
        {
            ++filledTableElementsCount;
            size_t listLength = getLength(hashTable->array[i]);
            wordsCount += listLength;
            maxListLength = max(maxListLength, listLength);
        }
    }
    printf("Fill factor: %f\n", (float)filledTableElementsCount / hashTable->size);
    printf("The maximum and average length of the list in the table segment: %lld and %f\n",
        maxListLength, (float)wordsCount / filledTableElementsCount);
}
