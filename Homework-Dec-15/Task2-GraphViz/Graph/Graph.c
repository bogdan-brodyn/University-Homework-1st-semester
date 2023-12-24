#include "Graph.h"

struct Graph
{
    size_t nodesCount;
    int** matrix;
};

static Graph* createGraph(const size_t nodesCount)
{
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    if (graph == NULL)
    {
        return NULL;
    }
    graph->nodesCount = nodesCount;
    graph->matrix = (int**)calloc(nodesCount, sizeof(int*));
    if (graph->matrix == NULL)
    {
        free(graph);
        return NULL;
    }
    for (size_t node = 0; node < nodesCount; ++node)
    {
        graph->matrix[node] = (int*)calloc(nodesCount, sizeof(int));
        if (graph->matrix[node] == NULL)
        {
            deleteGraph(&graph);
            return NULL;
        }
    }
    return graph;
}

Graph* getGraph(FILE* stream)
{
    size_t n = 0;
    fscanf_s(stream, "%lld", &n);
    Graph* graph = createGraph(n);
    if (graph == NULL)
    {
        return NULL;
    }
    for (size_t node1 = 0; node1 < n; ++node1)
    {
        for (size_t node2 = 0; node2 < n; ++node2)
        {
            fscanf_s(stream, "%d", &graph->matrix[node1][node2]);
        }
    }
    return graph;
}

void deleteGraph(Graph** const graph)
{
    if (graph == NULL || *graph == NULL)
    {
        return;
    }
    for (size_t node = 0; node < (*graph)->nodesCount; ++node)
    {
        free((*graph)->matrix[node]);
    }
    free((*graph)->matrix);
    free(*graph);
    *graph = NULL;
}

void writeDotFormat(FILE* stream, const Graph* const graph)
{
    fprintf(stream, "strict graph {\n");
    for (size_t node1 = 0; node1 < graph->nodesCount; ++node1)
    {
        fprintf(stream, "    %lld -- {", node1);
        for (size_t node2 = 0; node2 < graph->nodesCount; ++node2)
        {
            if (graph->matrix[node1][node2] == 1)
            {
                fprintf(stream, " %lld", node2);
            }
        }
        fprintf(stream, " }\n");
    }
    fprintf(stream, "}\n");
}
