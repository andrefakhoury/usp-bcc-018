#ifndef GRAPH_H
#define GRAPH_H

#include "error.h"
#include <stdbool.h>
#include <stddef.h>


typedef struct Graph Graph;

Graph* graph_create(size_t qttVertex);
void addEdge(Graph* g, int u, int v, int w);
void removeEdge(Graph* g, int u, int v, int w);
void destroy(Graph* g);

#endif