#include "graph.h"
#include <stdlib.h>
#include <stdio.h>

#define min(a, b) (a < b ? a : b)

struct graph {
	int vertex;
	elem** mat;
};

Graph* createGraph(int* n, bool* error) {
	Graph* g = malloc(sizeof (Graph));

	if (g == NULL) {
		*error = true;
		return NULL;
	}

	g->vertex = *n;

	g->mat = calloc(*n, sizeof(int*));
	if (g->mat == NULL) {
		*error = true;
		return NULL;
	}

	for (int i = 0; i < *n; i++) {
		g->mat[i] = calloc(*n, sizeof(int));
		if (g->mat[i] == NULL) {
			*error = true;
			return NULL;
		}
	}

	for (int i = 0; i < *n; i++) {
		for (int j = 0; j < *n; j++) {
			g->mat[i][j] = NOEDGE;
		}
	}

	*error = false;
	return g;
}

void destroyGraph(Graph* g) {
	if (g == NULL)
		return;

	if (g->mat == NULL) {
		free(g);
		return;
	}

	for (int i = 0; i < g->vertex; i++)
		if (g->mat[i] != NULL)
			free(g->mat[i]);

	free(g->mat);
	free(g);
}

void addEdge(Graph* g, int* u, int* v, elem* w, bool* error) {
	if (*u >= g->vertex || *v >= g->vertex) {
		*error = true;
	} else {
		*error = false;
		g->mat[*u][*v] = *w;
	}
}

void removeEdge(Graph* g, int* u, int* v, bool* error) {
	if (*u >= g->vertex || *v >= g->vertex) {
		*error = true;
	} else {
		*error = false;
		g->mat[*u][*v] = NOEDGE;
	}
}

bool checkEdge(Graph* g, int* u, int* v) {
	return *u < g->vertex && *v < g->vertex && g->mat[*u][*v];
}

int dfs(Graph* g, int u, int v, int vis) {
	vis |= 1 << u;
	if (u == v) return 0;

	int ret = 0x3f3f3f3f;
	for (int i = 0; i < g->vertex; i++) {
		if (g->mat[u][i] != NOEDGE) {
			if (!(vis&(1<<i)))
				ret = min(ret, g->mat[u][i] + dfs(g, i, v, vis));
		}
	}

	return ret;
}

int dist(Graph* g, int* u, int* v) {
	return dfs(g, *u, *v, 0);
}

void transposeGraph(Graph* g, bool* error) {
	if (g == NULL) {
		*error = true;
		return;
	}

	for (int i = 0; i < g->vertex; i++) {
		for (int j = i+1; j < g->vertex; j++) {
			elem aux = g->mat[i][j];
			g->mat[i][j] = g->mat[j][i];
			g->mat[j][i] = aux;
		}
	}

	*error = false;
}

Graph* genTranspostGraph(Graph* g, bool* error) {
	Graph *ng = createGraph(&g->vertex, error);

	for (int i = 0; i < g->vertex; i++) {
		for (int j = 0; j < g->vertex; j++) {
			ng->mat[i][j] = g->mat[j][i];
		}
	}

	*error = false;
	return ng;
}

bool emptyAdjList(Graph* g, int* u, bool* error) {
	if (*u >= g->vertex)
		return *error = true;

	*error = false;
	bool empty = true;

	for (int i = 0; i < g->vertex; i++)
		if (g->mat[*u][i] != NOEDGE) empty = false;

	return empty;
}

int firstAdjList(Graph* g, int* u, bool* error) {
	if (*u >= g->vertex)
		return *error = true;

	*error = false;

	for (int i = 0; i < g->vertex; i++)
		if (g->mat[*u][i] != NOEDGE)
			return i;

	return -1;
}

void printGraph(Graph* g) {
	int n = g->vertex;
	
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (g->mat[i][j] != NOEDGE) {
				printf("(%d, %d) ", i, j);
			}
		}
	}
	printf("\n");
}

void smallestEdge(Graph* g, int* u, int* v, bool* error) {
	if (g == NULL) *error = true;
	else {
		*error = false;
		elem smallest = 0x3f3f3f3f;

		for (int i = 0; i < g->vertex; i++) {
			for (int j = 0; j < g->vertex; j++) {
				if (g->mat[i][j] != NOEDGE) {
					if (g->mat[i][j] < smallest) {
						smallest = g->mat[i][j];
						*u = i;
						*v = j;
					}
				}
			}
		}
	}
}

int** vertexByDegree(Graph* g, bool* error) {
	if (g == NULL) {
		*error = true;
		return NULL;
	}

	int* qtt = calloc(g->vertex + 1, sizeof(int));
	if (qtt == NULL) {
		*error = true;
		return NULL;
	}

	int** deg = calloc(g->vertex + 1, sizeof(int*));
	if (deg == NULL) {
		free(qtt);
		*error = true;
		return NULL;
	}

	for (int i = 0; i < g->vertex; i++) {
		int d = 0;
		for (int j = 0; j < g->vertex; j++) {
			d += g->mat[i][j] != NOEDGE;
		}
		deg[d] = realloc(deg[d], ++qtt[d] * sizeof(int));
		deg[d][qtt[d]-1] = i;
	}

	// for (int i = 0; i <= g->vertex; i++) {
	// 	printf("%d: ", i);
	// 	for (int j = 0; j < qtt[i]; j++) {
	// 		printf("%d ", deg[i][j]);
	// 	}
	// 	printf("\n");
	// }

	free(qtt);
	return deg;
}

