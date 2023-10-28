#include <stdlib.h>
#include <stdbool.h>

#include "Stack.h"

typedef struct
{
    int value;
    struct StructElement* next;
} StackElement;

struct Stack
{
    StackElement* top;
};

Stack* const createStack(void)
{
    return (Stack* const)calloc(1, sizeof(Stack));
}

StackErrorCode deleteStack(Stack** stack)
{
    if (stack == NULL)
    {
        return nullPtr;
    }
    while (!isEmpty(*stack))
    {
        pop(*stack);
    }
    free(*stack);
    *stack = NULL;
    return defaultErrorCode;
}

StackErrorCode push(Stack* stack, int value)
{
    if (stack == NULL)
    {
        return nullPtr;
    }
    StackElement* const newStackElement = (StackElement* const)malloc(sizeof(StackElement));
    if (newStackElement == NULL)
    {
        return memoryLack;
    }
    newStackElement->value = value;
    newStackElement->next = stack->top;
    stack->top = newStackElement;
    return defaultErrorCode;
}

StackErrorCode pop(Stack* stack)
{
    if (stack == NULL)
    {
        return nullPtr;
    }
    if (isEmpty(stack))
    {
        return stackEmpty;
    }
    StackElement* stackElementToPop = stack->top;
    stack->top = stack->top->next;
    free(stackElementToPop);
    return defaultErrorCode;
}

StackErrorCode top(Stack* stack, int* topStackElementValue)
{
    if (stack == NULL)
    {
        return nullPtr;
    }
    if (isEmpty(stack))
    {
        return stackEmpty;
    }
    *topStackElementValue = stack->top->value;
    return defaultErrorCode;
}

bool isEmpty(Stack* stack)
{
    return stack == NULL || stack->top == NULL;
}
