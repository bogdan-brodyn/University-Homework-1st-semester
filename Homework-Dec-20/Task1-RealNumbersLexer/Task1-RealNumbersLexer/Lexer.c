#include "Lexer.h"

typedef enum
{
    begin,
    notANumber,
    integerPart,
    fractionalPartBegin,
    fractionalPart,
    exponentBegin,
    sign,
    exponent
} State;

#define FINAL_STATES_COUNT 3

State FINAL_STATES[FINAL_STATES_COUNT] = { integerPart, fractionalPart, exponent };

static int move(State state, char symbol)
{
    switch (state)
    {
    case begin:
        if ('0' <= symbol && symbol <= '9')
        {
            return integerPart;
        }
        return notANumber;
    case notANumber:
        return notANumber;
    case integerPart:
        if ('0' <= symbol && symbol <= '9')
        {
            return integerPart;
        }
        if (symbol == '.')
        {
            return fractionalPartBegin;
        }
        if (symbol == 'e' || symbol == 'E')
        {
            return exponentBegin;
        }
        return notANumber;
    case fractionalPartBegin:
        if ('0' <= symbol && symbol <= '9')
        {
            return fractionalPart;
        }
        return notANumber;
    case fractionalPart:
        if ('0' <= symbol && symbol <= '9')
        {
            return fractionalPart;
        }
        if (symbol == 'e' || symbol == 'E')
        {
            return exponentBegin;
        }
        return notANumber;
    case exponentBegin:
        if ('0' <= symbol && symbol <= '9')
        {
            return exponent;
        }
        if (symbol == '+' || symbol == '-')
        {
            return sign;
        }
        return notANumber;
    case sign:
        if ('0' <= symbol && symbol <= '9')
        {
            return exponent;
        }
        return notANumber;
    case exponent:
        if ('0' <= symbol && symbol <= '9')
        {
            return exponent;
        }
        return notANumber;
    }
}

bool isNumber(const char* const string)
{
    State state = begin;
    for (size_t i = 0; string[i] != '\0'; ++i)
    {
        state = move(state, string[i]);
    }
    for (size_t i = 0; i < FINAL_STATES_COUNT; ++i)
    {
        if (FINAL_STATES[i] == state)
        {
            return true;
        }
    }
    return false;
}
