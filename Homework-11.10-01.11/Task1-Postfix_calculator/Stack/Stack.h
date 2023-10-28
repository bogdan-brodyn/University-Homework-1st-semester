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

StackErrorCode push(Stack* const stack, const int value);

StackErrorCode pop(Stack* const stack);

StackErrorCode top(const Stack* const stack, int* const topStackElementValue);

bool isEmpty(const Stack* const stack);
