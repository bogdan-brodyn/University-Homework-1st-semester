#include "PriorityQueue.h"

struct PriorityQueue
{
    size_t size;
    size_t capacity;
    PriorityQueueValue* array;
};

bool isEmpty(const PriorityQueue* const queue)
{
    return queue == NULL || queue->size == 1;
}

static PriorityQueue* createPriorityQueue(void)
{
    PriorityQueue* newQueue = (PriorityQueue*)calloc(1, sizeof(PriorityQueue));
    if (newQueue == NULL)
    {
        return NULL;
    }
    newQueue->size = 1;
    newQueue->capacity = 2;
    newQueue->array = (PriorityQueueValue*)calloc(2, sizeof(PriorityQueueValue));
    if (newQueue->array == NULL)
    {
        free(newQueue);
        return NULL;
    }
    return newQueue;
}

static void swap(PriorityQueueValue* const array,
    const size_t index1, const size_t index2)
{
    PriorityQueueValue temp = array[index1];
    array[index1] = array[index2];
    array[index2] = temp;
}

static void siftDown(PriorityQueue* const queue, size_t index)
{
    PriorityQueueValue* const array = queue->array;
    while (index * 2 < queue->size)
    {
        if (index * 2 + 1 < queue->size
            && compare(array[index * 2], array[index * 2 + 1]) > 0
            && compare(array[index], array[index * 2 + 1]) > 0)
        {
            swap(array, index, index * 2 + 1);
            index = index * 2 + 1;
            continue;
        }
        if (compare(array[index], array[index * 2]) > 0)
        {
            swap(array, index, index * 2);
            index *= 2;
            continue;
        }
        return;
    }
}

static void siftUp(PriorityQueue* const queue, size_t index)
{
    PriorityQueueValue* const array = queue->array;
    while (index > 1 && compare(array[index / 2], array[index]) > 0)
    {
        swap(array, index / 2, index);
        index /= 2;
    }
}

PriorityQueueErrorCode push(PriorityQueue** const queue,
    const PriorityQueueValue value)
{
    if (*queue == NULL)
    {
        *queue = createPriorityQueue();
        if (*queue == NULL)
        {
            return memoryLackPriorityQueueErrorCode;
        }
    }

    if ((*queue)->size >= (*queue)->capacity)
    {
        PriorityQueueValue* temp = (PriorityQueueValue*)realloc(
            (*queue)->array, 2 * (*queue)->capacity * sizeof(PriorityQueueValue));
        if (temp == NULL)
        {
            return memoryLackPriorityQueueErrorCode;
        }
        (*queue)->array = temp;
        (*queue)->capacity *= 2;
    }
    (*queue)->array[(*queue)->size++] = value;
    siftUp(*queue, (*queue)->size - 1);
    return defaultPriorityQueueErrorCode;
}

PriorityQueueValue popMinValue(PriorityQueue* const queue)
{
    PriorityQueueValue min = queue->array[1];
    swap(queue->array, 1, queue->size - 1);
    --queue->size;
    siftDown(queue, 1);
    return min;
}

void deleteQueue(PriorityQueue** const queue)
{
    if (queue == NULL || *queue == NULL)
    {
        return;
    }
    free((*queue)->array);
    free(*queue);
    *queue = NULL;
}
