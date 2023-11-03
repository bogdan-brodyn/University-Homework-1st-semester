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
    *isCorrect &= isEmpty(stack);
    deleteStack(&stack);
    return bracketSequenceDefaultErrorCode;
}
