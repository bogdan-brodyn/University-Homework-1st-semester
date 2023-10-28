#include <stdio.h>
#include <stdlib.h>

#include "../Stack/Stack.h"
#include "Postfix_calculator.h"

char* get_string(CalculatorErrorCode* errorCode) {
    int inputStringLength = 0;
    int inputStringCapacity = 1;
    char* inputString = (char*)malloc(sizeof(char));
    char newChar = getchar();
    while (newChar != '\n') {
        inputString[(inputStringLength)++] = newChar;
        if (inputStringLength >= inputStringCapacity) {
            inputStringCapacity *= 2;
            char* const temp = (char*)realloc(inputString, inputStringCapacity * sizeof(char));
            if (temp == NULL)
            {
                *errorCode = calculatorMemoryLack;
                free(inputString);
                return NULL;
            }
            inputString = temp;
        }
        newChar = getchar();
    }
    inputString[inputStringLength] = '\0';
    *errorCode = calculatorDefaultErrorCode;
    return inputString;
}

int main(void)
{
    printf("Enter arithmetic expression in postfix form: ");
    CalculatorErrorCode mathExpressionErrorCode = defaultErrorCode;
    char* const mathExpression = get_string(&mathExpressionErrorCode);
    if (mathExpressionErrorCode == calculatorMemoryLack)
    {
        printf("Program could not read the data from the console\n");
        return calculatorMemoryLack;
    }

    int mathExpressionResult = 0;
    CalculatorErrorCode errorCode = getMathExpressionResult(mathExpression, &mathExpressionResult);
    if (errorCode == calculatorInvalidInput)
    {
        printf("Math expression is incorrect\n");
    }
    else if (errorCode == calculatorMemoryLack)
    {
        printf("Program Executed urgently because of memory lack\n");
    }
    else
    {
        printf("Result = %d\n", mathExpressionResult);
    }
    free(mathExpression);
    return errorCode;
}
