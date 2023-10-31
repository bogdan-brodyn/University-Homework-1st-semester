#pragma once

#include <stdbool.h>

typedef enum
{
    defaultErrorCode,
    memoryLack,
    nullPtr,
    stackEmpty
} StackErrorCode;

typedef struct Stack Stack;

Stack* const createStack(void);

void deleteStack(Stack** const stack);

StackErrorCode push(Stack* const stack, const char value);

StackErrorCode pop(Stack* const stack);

StackErrorCode top(const Stack* const stack, char* const topStackElementValue);

bool isEmpty(const Stack* const stack);
