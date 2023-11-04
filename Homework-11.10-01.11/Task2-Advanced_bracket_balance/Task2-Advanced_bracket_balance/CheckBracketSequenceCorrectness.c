#include <stdlib.h>

#include "CheckBracketSequenceCorrectness.h"
#include "../Stack/Stack.h"

BracketSequenceErrorCode checkBracketSequenceCorrectness(const char* const bracketSequence, bool* const isCorrect)
{
    Stack* stack = createStack();
    if (stack == NULL)
    {
        return bracketSequenceMemoryLack;
    }

    *isCorrect = true;
    for (size_t i = 0; bracketSequence[i] != '\0'; ++i)
    {
        const char currentChar = bracketSequence[i];
        if (currentChar == '(' || currentChar == '[' || currentChar == '{')
        {
            push(stack, currentChar);
            continue;
        }
        if (currentChar != ')' && currentChar != ']' && currentChar != '}')
        {
            continue;
        }
        char lastOpenBracket = 0;
        if (top(stack, &lastOpenBracket) == stackEmpty)
        {
            *isCorrect = false;
            break;
        }
        pop(stack);
        if (lastOpenBracket == '(' && currentChar != ')'
            || lastOpenBracket == '[' && currentChar != ']'
            || lastOpenBracket == '{' && currentChar != '}')
        {
            *isCorrect = false;
            break;
        }
    }
    *isCorrect &= isEmpty(stack);
    deleteStack(&stack);
    return bracketSequenceDefaultErrorCode;
}
