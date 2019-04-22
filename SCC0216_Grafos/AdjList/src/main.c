#include "graph.h"
#include <stdio.h>
#include <stdbool.h>

int main() {
	bool error;
	Graph* g = graph_create(3, &error);

	addEdge(g, 1, 2, 4, &error);
	printf("%d\n", error);

	removeEdge(g, 1, 2, 4, &error);
}