#pragma once

#include <stdlib.h>
#include <stdbool.h>

typedef enum
{
    defaultPriorityQueueErrorCode,
    memoryLackPriorityQueueErrorCode
} PriorityQueueErrorCode;

typedef struct PriorityQueueValue
{
    size_t node;
    size_t colour;
    size_t length;
} PriorityQueueValue;

inline int compare(const PriorityQueueValue value1,
    const PriorityQueueValue value2)
{
    return (int)value1.length - value2.length;
}

typedef struct PriorityQueue PriorityQueue;

bool isEmpty(const PriorityQueue* const queue);

PriorityQueueErrorCode push(PriorityQueue** const queue, 
    const PriorityQueueValue value);

PriorityQueueValue popMinValue(PriorityQueue* const queue);

void deleteQueue(PriorityQueue** const queue);
