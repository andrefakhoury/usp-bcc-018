#include "graph.h"
#include <stdlib.h>

typedef struct NodeEdge {
	int v;
	elem w;
	struct NodeEdge *next;
} NodeEdge;

typedef struct {
	NodeEdge *begin;
	int size;
} ListVertex;

struct Graph {
	ListVertex list[MAXN];
	int numV;
};

Graph* createGraph(int V) {
	Graph* g = malloc(sizeof(Graph));
	g->numV = V;

	for (int i = 0; i < V; i++) {
		g->list[i].begin = NULL;
		g->list[i].size = 0;
	}

	return g;
}

void destroyNode(NodeEdge* u) {
	if (u == NULL) return;

	destroyNode(u->next);
	free(u);
}

void destroyGraph(Graph* g) {
	if (g == NULL) return;

	for (int u = 0; u < g->numV; u++)
		destroyNode(g->list[u].begin);

	free(g);
}

int addEdge(Graph* g, int u, int v, elem w) {
	if (g->numV <= u || g->numV <= v) return 0;

	NodeEdge* newEdge = malloc(sizeof(newEdge));
	newEdge->v = v;
	newEdge->w = w;
	newEdge->next = NULL;

	NodeEdge* prev = g->list[u].begin;
	if (prev == NULL) g->list[u].begin = newEdge;
	else {
		while (prev->next != NULL) prev = prev->next;
		prev->next = newEdge;
	}

	g->list[u].size++;

	return 1;
}

int removeEdge(Graph* g, int u, int v) {
	if (g->numV <= u || g->numV <= v) return 0;
	
	NodeEdge* aux = g->list[u].begin;
	NodeEdge* prev = NULL;

	while (aux != NULL) {
		if (aux->v == v) {
			if (prev == NULL) g->list[u].begin = aux->next;
			else prev->next = aux->next;
			free(aux);
			g->list[u].size--;
			return 1;
		} else {
			prev = aux;
			aux = aux->next;
		}
	}

	return 0;
}

int edgeIsSet(Graph* g, int u, int v) {
	if (g == NULL) return 0;
	if (u >= g->numV) return 0;
	if (v >= g->numV) return 0;

	int isSet = 0;
	NodeEdge* aux = g->list[u].begin;
	while (aux != NULL && !isSet) {
		if (aux->v == v) isSet = 1;
		aux = aux->next;
	}

	return isSet;
}

int degreeOfVertex(Graph* g, int u) {
	return g->list[u].size;
}