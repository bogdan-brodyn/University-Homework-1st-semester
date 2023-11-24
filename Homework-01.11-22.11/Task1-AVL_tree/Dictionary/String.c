#include <stdlib.h>
#include <string.h>

#include "String.h"

char compare(const char* const string1, const char* const string2)
{
    for (size_t i = 0; string1[i] != '\0' || string2[i] != '\0'; ++i)
    {
        if (string1[i] != string2[i])
        {
            return string1[i] - string2[i];
        }
    }
    return 0;
}

char* getStringCopy(const char* const string)
{
    const size_t stringSize = strlen(string) + 1;
    char* stringCopy = (char*)malloc(stringSize * sizeof(char));
    errno_t errorCode = strcpy_s(stringCopy, stringSize, string);
    if (errorCode != 0)
    {
        free(stringCopy);
        return NULL;
    }
    return stringCopy;
}

char* getString(void)
{
    size_t inputStringLength = 0;
    size_t inputStringCapacity = 1;
    char* inputString = (char*)malloc(sizeof(char));
    if (inputString == NULL)
    {
        return NULL;
    }
    char newChar = getchar();
    while (newChar == ' ')
    {
        newChar = getchar();
    }
    while (newChar != '\n' && newChar != '-')
    {
        inputString[(inputStringLength)++] = newChar;
        if (inputStringLength >= inputStringCapacity) {
            inputStringCapacity *= 2;
            char* const temp = (char*)realloc(inputString, inputStringCapacity * sizeof(char));
            if (temp == NULL)
            {
                free(inputString);
                return NULL;
            }
            inputString = temp;
        }
        newChar = getchar();
    }
    inputString[inputStringLength] = '\0';
    return inputString;
}
