#include <stdio.h>
#include <stdlib.h>

#include "../Graph/Graph.h"
#include "../Graph/ColorizeStates.h"

#define TEST1_FILE_PATH "../input.txt"

#define DEFAULT_ERROR_CODE 0
#define FILE_NOT_FOUND_ERROR_CODE 1
#define MEMORY_LACK_ERROR_CODE 2

int main(void)
{
    FILE* file = NULL;
    if (fopen_s(&file, TEST1_FILE_PATH, "r") != 0)
    {
        printf("File not found\n");
        return FILE_NOT_FOUND_ERROR_CODE;
    }
    size_t n = 0;
    Graph* graph = getGraphFromStream(file, &n);
    if (graph == NULL)
    {
        printf("Memory lack\n");
        fclose(file);
        return MEMORY_LACK_ERROR_CODE;
    }
    size_t k = 0;
    size_t* capitals = getCapitalsFromStream(file, &k);
    if (capitals == NULL)
    {
        printf("Memory lack\n");
        deleteGraph(&graph);
        fclose(file);
        return MEMORY_LACK_ERROR_CODE;
    }
    fclose(file);

    size_t* colours = colorizeStates(graph, n, capitals, k);
    deleteGraph(&graph);
    free(capitals);
    if (colours == NULL)
    {
        printf("Memory lack\n");
        return MEMORY_LACK_ERROR_CODE;
    }
    for (size_t capital = 0; capital < k; ++capital)
    {
        printf("State %lld: ", capital + 1);
        for (size_t node = 0; node < n; ++node)
        {
            if (colours[node] == capital)
            {
                printf("%lld ", node);
            }
        }
        printf("\n");
    }
    free(colours);
    return DEFAULT_ERROR_CODE;
}
