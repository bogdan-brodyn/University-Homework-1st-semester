#include <stdio.h>
#include <stdlib.h>

#include "List.h"
#include "MergeSort.h"

#define DEFAULT_EXIT_CODE 0
#define FILE_WAS_NOT_FOUND_EXIT_CODE 1
#define BY_NAMES 1
#define BY_PHONE_NUMBERS 2

static char* getName(FILE* stream) {
    size_t inputStringLength = 0;
    size_t inputStringCapacity = 1;
    char* inputString = (char*)malloc(sizeof(char));
    if (inputString == NULL)
    {
        return NULL;
    }
    while (inputStringLength < 3 || 
        !(inputString[inputStringLength - 3] == ' '
        && inputString[inputStringLength - 2] == '-'
        && inputString[inputStringLength - 1] == ' '))
    {
        char newChar = fgetc(stream);
        inputString[(inputStringLength)++] = newChar;
        if (inputStringLength >= inputStringCapacity) {
            inputStringCapacity *= 2;
            char* const temp = (char*)realloc(inputString, inputStringCapacity * sizeof(char));
            if (temp == NULL)
            {
                free(inputString);
                return NULL;
            }
            inputString = temp;
        }
    }
    inputString[inputStringLength - 3] = '\0';
    return inputString;
}

int main(void)
{
    FILE* file = NULL;
    fopen_s(&file, "../input.txt", "r");
    if (file == NULL)
    {
        printf("File was not found\n");
        return FILE_WAS_NOT_FOUND_EXIT_CODE;
    }

    List* list = NULL;
    while (!feof(file))
    {
        char* name = getName(file);
        unsigned long long phoneNumber = 0;
        fscanf_s(file, "%lld\n", &phoneNumber);
        pushBack(&list, createListElement(name, phoneNumber));
        free(name);
    }
    fclose(file);

    int sortingType = 0;
    printf("If you want to sort the data by names, enter %d\n", BY_NAMES);
    printf("If you want to sort the data by phone numbers, enter %d\n", BY_PHONE_NUMBERS);
    scanf_s("%d", &sortingType);
    Compare compare = sortingType == BY_NAMES ? compareByName : compareByPhoneNumber;
    mergeSort(&list, compare);

    printList(list);
    deleteList(&list);
    return DEFAULT_EXIT_CODE;
}
