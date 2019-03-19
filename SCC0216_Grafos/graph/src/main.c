#include "graph.h"
#include <stdio.h>

int main() {
	int n = 10, u, v, w;
	bool error;

	Graph* g = createGraph(&n, &error);

	u = 1, v = 2, w = 1; addEdge(g, &u, &v, &w, &error);
	u = 2, v = 3, w = 1; addEdge(g, &u, &v, &w, &error); 
	u = 3, v = 4, w = 1; addEdge(g, &u, &v, &w, &error);
	u = 4, v = 1, w = 1; addEdge(g, &u, &v, &w, &error);

	euler(g);

	destroyGraph(g);
}