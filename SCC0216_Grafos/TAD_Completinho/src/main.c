#include "graph.h"
#include "error.h"
#include <stdlib.h>
#include <stdio.h>

int main() {
	Graph* graph = graph_create(5);
	addEdge(graph, 1, 2, 1);
	removeEdge(graph, 1, 2, 1);
	destroy(graph);
}