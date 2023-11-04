#include <stdio.h>
#include <stdlib.h>

#include "../Stack/Stack.h"
#include "CheckBracketSequenceCorrectness.h"

static char* get_string(BracketSequenceErrorCode* errorCode) {
    size_t inputStringLength = 0;
    size_t inputStringCapacity = 1;
    char* inputString = (char*)malloc(sizeof(char));
    if (inputString == NULL)
    {
        *errorCode = bracketSequenceMemoryLack;
        return NULL
    }
    char newChar = getchar();
    while (newChar != '\n') {
        inputString[(inputStringLength)++] = newChar;
        if (inputStringLength >= inputStringCapacity) {
            inputStringCapacity *= 2;
            char* const temp = (char*)realloc(inputString, inputStringCapacity * sizeof(char));
            if (temp == NULL)
            {
                *errorCode = bracketSequenceMemoryLack;
                free(inputString);
                return NULL;
            }
            inputString = temp;
        }
        newChar = getchar();
    }
    inputString[inputStringLength] = '\0';
    *errorCode = bracketSequenceDefaultErrorCode;
    return inputString;
}

int main(void)
{
    printf("Enter bracket sequence: ");
    BracketSequenceErrorCode bracketSequenceErrorCode = defaultErrorCode;
    char* const bracketSequence = get_string(&bracketSequenceErrorCode);
    if (bracketSequenceErrorCode == bracketSequenceMemoryLack)
    {
        printf("Program could not read the data from the console\n");
        return bracketSequenceMemoryLack;
    }

    bool isBracketSequenceCorrect = false;
    BracketSequenceErrorCode errorCode = checkBracketSequenceCorrectness(bracketSequence, &isBracketSequenceCorrect);
    if (errorCode == bracketSequenceMemoryLack)
    {
        printf("Program had been executed urgently because of memory lack\n");
    }
    else
    {
        printf(isBracketSequenceCorrect ? "Bracket sequence is correct\n" : "Bracket sequence is incorrect\n");
    }

    free(bracketSequence);
    return bracketSequenceDefaultErrorCode;
}
