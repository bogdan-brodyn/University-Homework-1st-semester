#include <stdlib.h>

#include "Postfix_calculator.h"
#include "../Stack/Stack.h"

int calculate(const char sign, const int number1, const int number2)
{
    switch (sign)
    {
    case '+':
        return number1 + number2;
    case '-':
        return number1 - number2;
    case '*':
        return number1 * number2;
    case '/':
        return number1 / number2;
    }
}

CalculatorErrorCode getMathExpressionResult(const char* const mathExpression, int* result)
{
    Stack* stack = createStack();
    if (stack == NULL)
    {
        return calculatorMemoryLack;
    }

    for (size_t i = 0; mathExpression[i] != '\0'; ++i)
    {
        if (mathExpression[i] == ' ')
        {
            continue;
        }
        if ('0' <= mathExpression[i] && mathExpression[i] <= '9')
        {
            push(stack, (int)(mathExpression[i] - '0'));
            continue;
        }
        int topStackElement1 = 0;
        int topStackElement2 = 0;
        if (top(stack, &topStackElement1) != defaultErrorCode)
        {
            deleteStack(&stack);
            return calculatorInvalidInput;
        }
        pop(stack);
        if (top(stack, &topStackElement2) != defaultErrorCode)
        {
            deleteStack(&stack);
            return calculatorInvalidInput;
        }
        pop(stack);
        push(stack, calculate(mathExpression[i], topStackElement2, topStackElement1));
    }
    top(stack, result);
    pop(stack);
    if (!isEmpty(stack))
    {
        return calculatorInvalidInput;
    }
    deleteStack(&stack);
    return calculatorDefaultErrorCode;
}
