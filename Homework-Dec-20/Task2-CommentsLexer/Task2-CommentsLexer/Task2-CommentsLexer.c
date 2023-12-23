#include <stdio.h>

#include "Lexer.h"

#define DEFAULT_EXIT_CODE 0
#define FILE_NOT_FOUND 1
#define INPUT_PATH "input.txt"

int main(void)
{
    FILE* file = NULL;
    fopen_s(&file, INPUT_PATH, "r");
    if (file == NULL)
    {
        printf("File not found\n");
        return FILE_NOT_FOUND;
    }
    printComments(file);
    fclose(file);
    return DEFAULT_EXIT_CODE;
}
