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
    commentStart,
    comment,
    secondAsterisk,
    commentEnd
} State;

State matrix[6][3] = {
//        /            *         default
    {firstSlash, start,          start},
    {firstSlash, commentStart,   start},
    {comment,    secondAsterisk, comment},
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
    int commentsCounter = 0;
    while (feof(stream) == 0)
    {
        char currentChar = fgetc(stream);
        state = move(state, currentChar);
        switch (state)
        {
        case commentStart:
            printf("/*");
            break;
        case comment:
        case secondAsterisk:
            printf("%c", currentChar);
            break;
        case commentEnd:
            printf("/ - comment %d\n\n", ++commentsCounter);
            break;
        }
    }
    if (state == comment || state == secondAsterisk)
    {
        printf("Warning: Last comment didn't end correctly\n");
    }
}
