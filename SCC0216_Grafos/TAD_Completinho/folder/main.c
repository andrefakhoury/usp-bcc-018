#include "graph.h"
#include <stdio.h>

int main() {
	Graph* g = createGraph(10);

	addEdge(g, 1, 2, 5);
	addEdge(g, 1, 3, 10);

	removeEdge(g, 1, 2);

	printf("%d\n", edgeIsSet(g, 1, 2));
	printf("%d\n", edgeIsSet(g, 1, 3));

	printf("%d\n", degreeOfVertex(g, 1));

	destroyGraph(g);
}