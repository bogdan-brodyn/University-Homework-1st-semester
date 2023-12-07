#pragma once

#include <stdlib.h>

#include "Graph.h"

size_t* colorizeStates(const Graph* const graph, const size_t n,
    const size_t* const capitals, const size_t k);

size_t* getCapitalsFromStream(FILE* stream, size_t* const k);
