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

StackErrorCode deleteStack(Stack** stack);

StackErrorCode push(Stack* stack, int value);

StackErrorCode pop(Stack* stack);

StackErrorCode top(Stack* stack, int* topStackElementValue);

bool isEmpty(Stack* stack);
