#include "graph.h"
#include <stdio.h>

int main() {
	int n = 10;
	Graph* g = createGraph(n);

	addEdge(g, 0, 1);
	addEdge(g, 1, 2);
	addEdge(g, 2, 4);

	print(g, 0);

	printf("%d\n", dist(g, 0, 5));



}