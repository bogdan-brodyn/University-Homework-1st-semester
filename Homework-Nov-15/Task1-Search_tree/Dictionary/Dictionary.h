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
    const int key, const char* const value);

DictionaryErrorCode get(const Dictionary* const dictionary,
    const int key, char** const value);

bool isContained(const Dictionary* const dictionary, const int key);

void removeKey(Dictionary* const dictionary, const int key);

void deleteDictionary(Dictionary** const dictionary);
