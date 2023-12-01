#include <stdlib.h>
#include <stdbool.h>

#include "Graph.h"
#include "List.h"

struct Graph
{
    size_t nodesCount;
    List** graph;
    List** length;
};

void getNode(const Graph* const graph, const size_t node, 
    List** const neighbors, List** const lengths)
{
    *neighbors = graph->graph[node];
    *lengths = graph->length[node];
}

Graph* createGraph(const size_t nodesCount)
{
    Graph* newGraph = (Graph*)malloc(sizeof(Graph));
    if (newGraph == NULL)
    {
        return NULL;
    }
    newGraph->nodesCount = nodesCount;
    newGraph->graph = (List**)calloc(nodesCount, sizeof(List*));
    newGraph->length = (List**)calloc(nodesCount, sizeof(List*));
    if (newGraph->graph == NULL || newGraph->length == NULL)
    {
        free(newGraph->graph);
        free(newGraph->length);
        free(newGraph);
        return NULL;
    }
    return newGraph;
}

GraphErrorCode newEdge(Graph* const graph, 
    const size_t node1, const size_t node2, const size_t length)
{
    ListErrorCode errorCode1 = pushBack(&graph->graph[node1], node2);
    ListErrorCode errorCode2 = pushBack(&graph->length[node1], length);
    ListErrorCode errorCode3 = pushBack(&graph->graph[node2], node1);
    ListErrorCode errorCode4 = pushBack(&graph->length[node2], length);
    if (errorCode1 != defaultListErrorCode || errorCode2 != defaultListErrorCode
        || errorCode3 != defaultListErrorCode || errorCode4 != defaultListErrorCode)
    {
        return memoryLackGraphErrorCode;
    }
    return defaultGraphErrorCode;
}

void deleteGraph(Graph** const graph)
{
    if (graph == NULL || *graph == NULL)
    {
        return;
    }
    for (size_t v = 0; v < (*graph)->nodesCount; ++v)
    {
        deleteList(&((*graph)->graph[v]));
        deleteList(&((*graph)->length[v]));
    }
    free((*graph)->graph);
    free((*graph)->length);
    free(*graph);
    *graph = NULL;
}

Graph* getGraphFromStream(FILE* stream, size_t* const n)
{
    size_t m = 0;
    fscanf_s(stream, "%lld %lld", n, &m);
    Graph* graph = createGraph(*n);
    if (graph == NULL)
    {
        return NULL;
    }
    for (size_t t = 0; t < m; ++t)
    {
        size_t i = 0;
        size_t j = 0;
        size_t len = 0;
        fscanf_s(stream, "%lld %lld %lld", &i, &j, &len);
        GraphErrorCode errorCode = newEdge(graph, i, j, len);
        if (errorCode != defaultGraphErrorCode)
        {
            deleteGraph(&graph);
            return NULL;
        }
    }
    return graph;
}
