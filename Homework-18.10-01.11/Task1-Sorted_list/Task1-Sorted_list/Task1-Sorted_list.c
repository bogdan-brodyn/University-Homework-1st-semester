#include <stdio.h>
#include <stdbool.h>

#include "SortedList.h"

#define MEMORY_LACK 1

int main(void)
{
    SortedList* sortedList = createSortedList();
    if (sortedList == NULL)
    {
        printf("Program has executed urgently because of memory lack\n");
        return MEMORY_LACK;
    }
    while (true)
    {
        int command = 0;
        printf("Enter command: ");
        scanf_s("%d", &command);
        if (command == 0)
        {
            printf("The program had been executed successfully\n");
            break;
        }
        if (command == 1)
        {
            int value = 0;
            scanf_s("%d", &value);
            SortedListError errorCode = addValue(sortedList, value);
            if (errorCode == sortedListDefaultErrorCode)
            {
                printf("Value had been successfully added\n");
            }
            else
            {
                printf("The program had been executed urgently because of an error\n");
                break;
            }
        }
        else if (command == 2)
        {
            int value = 0;
            scanf_s("%d", &value);
            SortedListError errorCode = deleteValue(sortedList, value);
            if (errorCode == sortedListDefaultErrorCode)
            {
                printf("Value had been successfully deleted\n");
            }
            else
            {
                printf("The program had been executed urgently because of an error\n");
                break;
            }
        }
        else
        {
            printf("Sorted list: ");
            printSortedList(sortedList);
        }
    }
    deleteSortedList(&sortedList);
    return 0;
}
