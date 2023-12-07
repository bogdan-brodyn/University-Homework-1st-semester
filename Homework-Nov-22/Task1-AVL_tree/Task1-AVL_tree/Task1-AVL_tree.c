#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../Dictionary/Dictionary.h"
#include "../Dictionary/String.h"

#define DEFAULT_EXIT_CODE 0
#define MEMORY_LACK 1

typedef enum
{
    exitCommand,
    addCommand,
    getCommand,
    isContainedCommand,
    removeKeyCommand
} Command;

static void dialogMode(Dictionary** const dictionary)
{
    while (true)
    {
        DictionaryErrorCode errorCode = dictionaryDefaultErrorCode;
        int command = 0;
        char* key = NULL;
        char* value = NULL;
        printf("Enter command: ");
        scanf_s("%d", &command);
        if (command == exitCommand)
        {
            printf("The program had been executed successfully\n");
            return;
        }
        key = getString();

        switch (command)
        {
        case addCommand:
            value = getString();
            if (value == NULL)
            {
                printf("Invalid input\n");
                return;
            }
            errorCode = add(dictionary, key, value);
            if (errorCode != dictionaryDefaultErrorCode)
            {
                printf("The program had been executed urgently because of an error\n");
                return;
            }
            printf("The key was successfully added\n");
            break;
        case getCommand:
            errorCode = get(*dictionary, key, &value);
            printf(errorCode == dictionaryDefaultErrorCode ?
                "Value: %s\n" : "Program has not found the key\n", value);
            break;
        case isContainedCommand:
            printf(isContained(*dictionary, key) ?
                "Key is contained\n" : "Key is not contained\n");
            break;
        case removeKeyCommand:
            removeKey(*dictionary, key);
            printf("Key was removed\n");
            break;
        default:
            printf("Invalid input\n");
        }
    }
}

int main(void)
{
    printf("If you want to exit, enter: %d\n", exitCommand);
    printf("If you want to add key, enter: %d key-value\n", addCommand);
    printf("If you want to get value by key, enter: %d key\n", getCommand);
    printf("If you want to check if the key is contained, enter: %d key\n", isContainedCommand);
    printf("If you want to remove key, enter: %d key\n", removeKeyCommand);
    Dictionary* dictionary = NULL;
    dialogMode(&dictionary);
    deleteDictionary(&dictionary);
    return DEFAULT_EXIT_CODE;
}
