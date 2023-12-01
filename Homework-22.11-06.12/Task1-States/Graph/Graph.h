#pragma once

#include <stdio.h>
#include <stdlib.h>

#include "List.h"

typedef enum
{
    defaultGraphErrorCode,
    memoryLackGraphErrorCode
} GraphErrorCode;

typedef struct Graph Graph;

void getNode(const Graph* const graph, const size_t node,
    List** const neighbors, List** const lengths);

Graph* createGraph(const size_t nodesCount);

GraphErrorCode newEdge(Graph* const graph,
    const size_t node1, const size_t node2, const size_t weight);

void deleteGraph(Graph** const graph);

Graph* getGraphFromStream(FILE* stream, size_t* const n);
