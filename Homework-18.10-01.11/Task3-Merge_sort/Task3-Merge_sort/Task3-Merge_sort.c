#include <stdio.h>
#include <stdlib.h>

#include "List.h"
#include "MergeSort.h"

#define FILE_WAS_NOT_FOUND 1
#define BY_NAMES 1
#define BY_PHONE_NUMBERS 2
#define MAX_NAME_LENGTH 100

int main(void)
{
    FILE* file = NULL;
    fopen_s(&file, "../input.txt", "r");
    if (file == NULL)
    {
        printf("File was not found\n");
        return FILE_WAS_NOT_FOUND;
    }

    List* list = NULL;
    char buffer[MAX_NAME_LENGTH];
    unsigned long long phoneNumber = 0;
    while (fscanf_s(file, "%s - %lld", &buffer, MAX_NAME_LENGTH, &phoneNumber) != EOF)
    {
        pushBack(&list, createListElement(buffer, phoneNumber));
    }

    int sortingType = 0;
    printf("If you want to sort the data by names, enter %d\n", BY_NAMES);
    printf("If you want to sort the data by phone numbers, enter %d\n", BY_PHONE_NUMBERS);
    scanf_s("%d", &sortingType);
    List* sortedList = sortingType == BY_NAMES ? 
        mergeSort(list, compareByName) : mergeSort(list, compareByPhoneNumber);

    while (!isEmpty(sortedList))
    {
        char* currentName = NULL;
        unsigned long long currentPhoneNumber = 0;
        getName(getFront(sortedList), &currentName);
        getPhoneNumber(getFront(sortedList), &currentPhoneNumber);
        printf("%s - %lld\n", currentName, currentPhoneNumber);
        popFront(sortedList);
    }

    fclose(file);
    deleteList(&list);
    deleteList(&sortedList);
}
