#include "graph.h"
#include "error.h"
#include <stdlib.h>
#include <stdio.h>

int main() {
	Error error;
	int n = 5;

	Graph* g = graph_create(n, sizeof(int), false, &error);

	int w = 1;

	graph_addEdge(g, 0, 1, &w, &error);



	w = 1; graph_addEdge(g, 0, 1, &w, &error);
	w = 2; graph_addEdge(g, 0, 2, &w, &error);
	w = 3; graph_addEdge(g, 1, 2, &w, &error);
	w = 4; graph_addEdge(g, 1, 3, &w, &error);
	w = 5; graph_addEdge(g, 1, 4, &w, &error);
	w = 6; graph_addEdge(g, 3, 4, &w, &error);

	// printf("%d\n", *(int*)graph_edgeWeight(g, 0, 1, &error));
	// printf("%d\n", *(int*)graph_edgeWeight(g, 0, 2, &error));
	// printf("%d\n", *(int*)graph_edgeWeight(g, 1, 2, &error));
	// printf("%d\n", *(int*)graph_edgeWeight(g, 1, 3, &error));
	// printf("%d\n", *(int*)graph_edgeWeight(g, 1, 4, &error));
	// printf("%d\n", *(int*)graph_edgeWeight(g, 3, 4, &error));

	int* color = malloc(n * sizeof(int));
	graph_welshPowell(g, color, &error);

	for (int i = 0; i < n; i++)
		printf("Cor de %d: %d\n", i, color[i]);

	free(color);

	graph_destroy(g, &error);
}