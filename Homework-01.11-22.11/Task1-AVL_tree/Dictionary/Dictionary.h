#pragma once

#include <stdbool.h>

typedef enum
{
    dictionaryDefaultErrorCode,
    dictionaryMemoryLack,
    dictionaryNullPointer,
    dictionaryUsedKey,
    dictionaryNonExistentKey
} DictionaryErrorCode;

typedef struct Dictionary Dictionary;

DictionaryErrorCode add(Dictionary** const dictionary,
    const char* const key, const char* const value);

DictionaryErrorCode get(const Dictionary* const dictionary,
    const char* const key, char** const value);

bool isContained(const Dictionary* const dictionary, const char* const key);

void removeKey(Dictionary* const dictionary, const char* const key);

void deleteDictionary(Dictionary** const dictionary);

bool checkBalance(const Dictionary* const dictionary);

size_t getSearchTreeHeight(const Dictionary* const dictionary);
