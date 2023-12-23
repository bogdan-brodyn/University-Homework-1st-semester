#include "Lexer.h"

typedef enum
{
    forwardSlash,
    asterisk,
    defaultCase
} Case;

typedef enum
{
    start,
    firstSlash,
    comment,
    secondAsterisk,
    commentEnd
} State;

State matrix[5][3] = {
//        /            *         default
    {firstSlash, start,          start},
    {firstSlash, comment,        start},
    {comment,    secondAsterisk, comment},
    {commentEnd, secondAsterisk, comment},
    {start,      start,          start}
};

static State move(const State state, const char symbol)
{
    switch (symbol)
    {
    case '/':
        return matrix[state][forwardSlash];
    case '*':
        return matrix[state][asterisk];
    default:
        return matrix[state][defaultCase];
    }
}

void printComments(FILE* stream)
{
    State state = start;
    char currentChar = 0;
    char previousChar = 0;
    while (feof(stream) == 0)
    {
        currentChar = fgetc(stream);
        state = move(state, currentChar);
        if (state == comment || state == secondAsterisk)
        {
            printf("%c", previousChar);
        }
        if (state == commentEnd)
        {
            printf("%c%c\n", previousChar, currentChar);
        }
        previousChar = currentChar;
    }
    if (state == comment || state == secondAsterisk || state == commentEnd)
    {
        printf("%c%c\n", previousChar, currentChar);
    }
}
