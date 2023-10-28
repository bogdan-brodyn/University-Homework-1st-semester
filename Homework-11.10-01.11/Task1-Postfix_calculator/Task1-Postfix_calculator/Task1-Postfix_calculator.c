#include <stdio.h>
#include <stdlib.h>

#include "../Stack/Stack.h"

typedef enum
{
    calculatorDefaultErrorCode,
    calculatorMemoryLack
} ErrorCode;

int calculate(const char sign, const int number1, const int number2)
{
    if (sign == '+')
    {
        return number1 + number2;
    }
    if (sign == '-')
    {
        return number1 - number2;
    }
    if (sign == '*')
    {
        return number1 * number2;
    }
    if (sign == '/')
    {
        return number1 / number2;
    }
}

ErrorCode getMathExpressionResult(const char* const mathExpression, int* result)
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
            push(stack, mathExpression[i] - '0');
            continue;
        }
        int topStackElement1 = 0;
        int topStackElement2 = 0;
        top(stack, &topStackElement1);
        pop(stack);
        top(stack, &topStackElement2);
        pop(stack);
        push(stack, calculate(mathExpression[i], topStackElement2, topStackElement1));
    }
    top(stack, result);
    deleteStack(&stack);
    return calculatorDefaultErrorCode;
}

int main(void)
{
    const int bufferSize = (const int)1e6;
    char* const mathExpression = (char* const)malloc(bufferSize * sizeof(char));
    if (mathExpression == NULL)
    {
        return calculatorMemoryLack;
    }
    scanf_s("%[^\n]s", mathExpression, bufferSize);

    int mathExpressionResult = 0;
    getMathExpressionResult(mathExpression, &mathExpressionResult);
    printf("%d\n", mathExpressionResult);

    free(mathExpression);
    return calculatorDefaultErrorCode;
}
