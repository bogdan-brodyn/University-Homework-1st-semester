#pragma once

typedef enum
{
    calculatorDefaultErrorCode,
    calculatorMemoryLack,
    calculatorInvalidInput
} CalculatorErrorCode;

int calculate(const char sign, const int number1, const int number2);

CalculatorErrorCode getMathExpressionResult(const char* const mathExpression, int* const result);
