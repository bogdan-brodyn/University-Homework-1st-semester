#include <stdio.h>

#include "../Graph/Graph.h"

#define DEFAULT_EXIT_CODE 0
#define FILE_NOT_FOUND 1
#define MEMORY_LACK 2

#define INPUT_PATH "input.txt"
#define OUTPUT_PATH "output.dot"

int main(void)
{
    FILE* input = NULL;
    fopen_s(&input, INPUT_PATH, "r");
    if (input == NULL)
    {
        printf("File not found\n");
        return FILE_NOT_FOUND;
    }
    FILE* output = NULL;
    fopen_s(&output, OUTPUT_PATH, "w");
    Graph* graph = getGraph(input);
    if (graph == NULL)
    {
        printf("Memory lack\n");
        return MEMORY_LACK;
    }
    writeDotFormat(output, graph);
    deleteGraph(&graph);
    printf("DOT file created successfully\n");
    return DEFAULT_EXIT_CODE;
}
