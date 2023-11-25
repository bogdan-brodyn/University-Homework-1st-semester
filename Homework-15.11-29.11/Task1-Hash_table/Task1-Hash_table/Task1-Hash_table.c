#include <stdio.h>
#include <locale.h>

#include "../HashTable/HashTable.h"
#include "../String/String.h"

#define DEFAULT_ERROR_CODE 0
#define FILE_NOT_FOUND 1

int main(void)
{
    setlocale(LC_ALL, "Russian");
    FILE* file = NULL;
    errno_t errorCode = fopen_s(&file, "../text.txt", "r");
    if (errorCode != 0)
    {
        printf("Program has not found the text file\n");
        return FILE_NOT_FOUND;
    }
    HashTable* hashTable = NULL;
    char* currentWord = getString(file);
    for (; !feof(file) && currentWord != NULL; currentWord = getString(file))
    {
        addWord(&hashTable, currentWord);
    }
    free(currentWord);
    fclose(file);

    printHashTable(hashTable);
    printf("\n");
    printAnalysisData(hashTable);
    deleteHashTable(&hashTable);
    return DEFAULT_ERROR_CODE;
}
