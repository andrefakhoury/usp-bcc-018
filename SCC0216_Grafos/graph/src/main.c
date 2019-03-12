#include "graph.h"
#include <stdio.h>

int main() {
	int n = 10, u, v, w;
	bool error;

	Graph* g = createGraph(&n, &error);

	u = 0, v = 1, w = 1; addEdge(g, &u, &v, &w, &error);
	u = 1, v = 3, w = 2; addEdge(g, &u, &v, &w, &error);
	u = 3, v = 5, w = 4; addEdge(g, &u, &v, &w, &error);

	printGraph(g);

	Graph* p = genTranspostGraph(g, &error);
	printGraph(p);

	int** degree = vertexByDegree(g, &error);

	
	destroyGraph(g);
}