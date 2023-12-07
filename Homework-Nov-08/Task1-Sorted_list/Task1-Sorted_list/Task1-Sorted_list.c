#include <stdio.h>
#include <stdbool.h>

#include "SortedList.h"

#define DEFAULT_EXIT_CODE 0
#define MEMORY_LACK 1

typedef enum
{
    exitCommand,
    addValueCommand,
    deleteValueCommand,
    printSortedListCommand
} Command;

static void printCommandResult(const SortedListError errorCode)
{
    printf(errorCode == sortedListDefaultErrorCode ? 
        "the command was executed successfully\n" :
        "The program had been executed urgently because of an error\n");
}

static void dialogMode(SortedList** const sortedList)
{
    while (true)
    {
        int command = 0;
        int value = 0;
        printf("Enter command: ");
        scanf_s("%d", &command);

        switch (command)
        {
        case exitCommand:
            printf("The program had been executed successfully\n");
            return;
        case addValueCommand:
            scanf_s("%d", &value);
            SortedListError errorCode = addValue(sortedList, value);
            printCommandResult(errorCode);
            if (errorCode != sortedListDefaultErrorCode)
            {
                return;
            }
            break;
        case deleteValueCommand:
            scanf_s("%d", &value);
            deleteValue(*sortedList, value);
            printCommandResult(sortedListDefaultErrorCode);
            break;
        case printSortedListCommand:
            printf("Sorted list: ");
            printSortedList(*sortedList);
            break;
        default:
            printf("Invalid input\n");
        }
    }
}

int main(void)
{
    SortedList* sortedList = NULL;
    dialogMode(&sortedList);
    deleteSortedList(&sortedList);
    return DEFAULT_EXIT_CODE;
}
