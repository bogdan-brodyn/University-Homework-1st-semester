#include <stdio.h>
#include <stdlib.h>

#include "../Stack/Stack.h"

typedef enum
{
    bracketSequenceDefaultErrorCode,
    bracketSequenceMemoryLack
} ErrorCode;

ErrorCode checkBracketSequenceCorrectness(const char* const bracketSequence, bool* isCorrect)
{
    Stack* stack = createStack();
    if (stack == NULL)
    {
        return bracketSequenceMemoryLack;
    }

    *isCorrect = true;
    for (size_t i = 0; bracketSequence[i] != '\0'; ++i)
    {
        if (bracketSequence[i] == '(' || bracketSequence[i] == '[' || bracketSequence[i] == '{')
        {
            push(stack, bracketSequence[i]);
            continue;
        }
        char lastOpenBracket = 0;
        if (top(stack, &lastOpenBracket) == stackEmpty)
        {
            *isCorrect = false;
            break;
        }
        pop(stack);
        if (lastOpenBracket == '(' && bracketSequence[i] != ')'
            || lastOpenBracket == '[' && bracketSequence[i] != ']'
            || lastOpenBracket == '{' && bracketSequence[i] != '}')
        {
            *isCorrect = false;
            break;
        }
    }
    *isCorrect = *isCorrect && isEmpty(stack);
    deleteStack(&stack);
    return bracketSequenceDefaultErrorCode;
}

int main(void)
{
    const int bufferSize = (const int)1e6;
    char* const bracketSequence = (char* const)malloc(bufferSize * sizeof(char));
    if (bracketSequence == NULL)
    {
        return bracketSequenceMemoryLack;
    }
    scanf_s("%s", bracketSequence, bufferSize);

    bool isBracketSequenceCorrect = 0;
    checkBracketSequenceCorrectness(bracketSequence, &isBracketSequenceCorrect);
    printf(isBracketSequenceCorrect ? "Bracket sequence is correct\n" : "Bracket sequence is incorrect\n");

    free(bracketSequence);
    return bracketSequenceDefaultErrorCode;
}
