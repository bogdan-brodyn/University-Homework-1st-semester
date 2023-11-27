#pragma once

#include <stdio.h>

char compare(const char* const string1, const char* const string2);

char* getStringCopy(const char* const string);

char* getString(FILE* stream);
