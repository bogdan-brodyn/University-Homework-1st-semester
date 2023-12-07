#include <stdlib.h>
#include <stdbool.h>

#include "ColorizeStates.h"
#include "PriorityQueue.h"
#include "Graph.h"
#include "List.h"

size_t* colorizeStates(const Graph* const graph, const size_t n,
    const size_t* const capitals, const size_t k)
{
    size_t* colours = (size_t*)malloc(n * sizeof(size_t));
    bool* used = (bool*)calloc(n, sizeof(bool));
    if (colours == NULL || used == NULL)
    {
        free(colours);
        free(used);
        return NULL;
    }
    PriorityQueue* queue = NULL;
    for (size_t v = 0; v < k; ++v)
    {
        PriorityQueueValue capital = { .node = capitals[v],
            .colour = v, .length = 0 };
        PriorityQueueErrorCode errorCode = push(&queue, capital);
        if (errorCode != defaultPriorityQueueErrorCode)
        {
            deleteQueue(&queue);
            free(colours);
            free(used);
            return NULL;
        }
    }
    while (!isEmpty(queue))
    {
        PriorityQueueValue minDistancedNode = popMinValue(queue);
        if (used[minDistancedNode.node])
        {
            continue;
        }
        used[minDistancedNode.node] = true;
        colours[minDistancedNode.node] = minDistancedNode.colour;
        List* neighbors = NULL;
        List* lengths = NULL;
        getNodeNeighbours(graph, minDistancedNode.node, &neighbors, &lengths);
        for (size_t neighbor = 0; neighbor < getSize(neighbors); ++neighbor)
        {
            PriorityQueueValue newQueueElement = { .node = get(neighbors, neighbor), 
                .colour = minDistancedNode.colour, 
                .length = minDistancedNode.length + get(lengths, neighbor) };
            PriorityQueueErrorCode errorCode = push(&queue, newQueueElement);
            if (errorCode != defaultPriorityQueueErrorCode)
            {
                deleteQueue(&queue);
                free(colours);
                free(used);
                return NULL;
            }
        }
    }
    deleteQueue(&queue);
    free(used);
    return colours;
}

size_t* getCapitalsFromStream(FILE* stream, size_t* const k)
{
    fscanf_s(stream, "%lld", k);
    size_t* capitals = (size_t*)malloc(*k * sizeof(size_t));
    if (capitals == NULL)
    {
        return NULL;
    }
    for (size_t t = 0; t < *k; ++t)
    {
        fscanf_s(stream, "%lld", &capitals[t]);
    }
    return capitals;
}
