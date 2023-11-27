#include <stdio.h>

#include "../HashTable/HashTable.h"
#include "../String/String.h"

#define DEFAULT_ERROR_CODE 0
#define FILE_NOT_FOUND 1
#define MEMORY_LACK_ERROR_CODE 2
#define RUNTIME_ERROR_CODE 3
#define INPUT_STREAM "../text.txt"

int main(void)
{
    size_t hashTableSize = 0;
    printf("Enter hash table size: ");
    scanf_s("%lld", &hashTableSize);

    FILE* file = NULL;
    errno_t errorCode = fopen_s(&file, INPUT_STREAM, "r");
    if (errorCode != 0)
    {
        printf("Program has not found the text file\n");
        return FILE_NOT_FOUND;
    }
    HashTable* hashTable = createHashTable(hashTableSize);
    if (hashTable == NULL)
    {
        printf("Memory lack\n");
        fclose(file);
        return MEMORY_LACK_ERROR_CODE;
    }
    char* currentWord = getString(file);
    for (; !feof(file) && currentWord != NULL; currentWord = getString(file))
    {
        HashTableErrorCode errorCode = addWord(hashTable, currentWord);
        if (errorCode != defaultHashTableErrorCode)
        {
            printf("Runtime error\n");
            fclose(file);
            free(currentWord);
            deleteHashTable(&hashTable);
            return RUNTIME_ERROR_CODE;
        }
    }
    free(currentWord);
    fclose(file);

    printHashTable(hashTable);
    printf("\n");
    printAnalysisData(hashTable);
    deleteHashTable(&hashTable);
    return DEFAULT_ERROR_CODE;
}
