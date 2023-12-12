#pragma once

#include <stdio.h>
#include <stdlib.h>

typedef struct Graph Graph;

Graph* getGraph(FILE* stream);

void deleteGraph(Graph** const graph);

void writeDotFormat(FILE* stream, const Graph* const graph);
