#include "graph.h"
#include <stdlib.h>

#define EMPTY 0

struct Graph {
	elem mat[MAXN][MAXN];
	int numV;
};

Graph* createGraph(int V) {
	Graph* g = malloc(sizeof(Graph));

	for (int i = 0; i < V; i++)
		for (int j = 0; j < V; j++)
			g->mat[i][j] = EMPTY;

	g->numV = V;
	return g;
}

void destroyGraph(Graph* g) {
	free(g);
}

int addEdge(Graph* g, int u, int v, elem w) {
	if (g->numV <= u || g->numV <= v) return 0;
	g->mat[u][v] = w;
	return 1;
}

int removeEdge(Graph* g, int u, int v) {
	if (g->numV <= u || g->numV <= v) return 0;
	g->mat[u][v] = EMPTY;
	return 1;
}

int edgeIsSet(Graph* g, int u, int v) {
	return g->mat[u][v] != EMPTY;
}

int degreeOfVertex(Graph* g, int u) {
	int ret = 0;
	for (int i = 0; i < g->numV; i++)
		ret += g->mat[u][i] != EMPTY;
	return ret;
}