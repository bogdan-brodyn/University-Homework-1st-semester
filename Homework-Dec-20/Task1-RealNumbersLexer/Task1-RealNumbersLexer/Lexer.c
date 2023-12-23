#include "Lexer.h"

#define F_SIZE 4
#define DIGIT 0
#define DOT 1
#define EXPONENT 2
#define SIGN 3
#define DEFAULT 4

int F[4] = { 2, 3, 4, 7 };

int matrix[8][5] = {
    // digit . E sign default
    {2, 1, 1, 1, 1}, // start
    {1, 1, 1, 1, 1}, // NAN
    {2, 3, 5, 1, 1}, // integer part
    {4, 1, 1, 1, 1}, // fractional part (first digit)
    {4, 1, 5, 1, 1}, // fractional part
    {7, 1, 1, 6, 1}, // exponent
    {7, 1, 1, 1, 1}, // sign
    {7, 1, 1, 1, 1}  // real number
};

static int move(int state, char symbol)
{
    if ('0' <= symbol && symbol <= '9')
    {
        return matrix[state][DIGIT];
    }
    if (symbol == '.')
    {
        return matrix[state][DOT];
    }
    if (symbol == 'e' || symbol == 'E')
    {
        return matrix[state][EXPONENT];
    }
    if (symbol == '+' || symbol == '-')
    {
        return matrix[state][SIGN];
    }
    return matrix[state][DEFAULT];
}

bool isNumber(char* string)
{
    int state = 0;
    for (size_t i = 0; string[i] != '\0'; ++i)
    {
        state = move(state, string[i]);
    }
    for (size_t i = 0; i < F_SIZE; ++i)
    {
        if (F[i] == state)
        {
            return true;
        }
    }
    return false;
}
