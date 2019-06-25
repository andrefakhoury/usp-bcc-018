#include "graph.h"

#include "graph.h"
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAXV 100

typedef struct EdgeNode {
	int v;
	int weight;
	struct EdgeNode *next;
} EdgeNode;

typedef struct {
	EdgeNode *begin, *end;
} VertexNode;

struct Graph {
	VertexNode adj[MAXV];
	size_t qttVertex;
};

Graph* graph_create(size_t qttVertex) {
	if (qttVertex >= MAXV) return NULL;

	Graph* g = malloc(sizeof(Graph));

	g->qttVertex = qttVertex;
	for (int i = 0; i < qttVertex; i++) {
		g->adj[i].begin = malloc(sizeof(EdgeNode));
		g->adj[i].begin->v = -1;
		g->adj[i].begin->weight = -1;
		g->adj[i].begin->next = NULL;
		g->adj[i].end = g->adj[i].begin;
	}

	return g;
}

void addEdge(Graph* g, int u, int v, int w) {
	if (u >= g->qttVertex || v >= g->qttVertex) return;

	g->adj[u].end->next = malloc(sizeof(EdgeNode));
	g->adj[u].end = g->adj[u].end->next;
	g->adj[u].end->v = v;
	g->adj[u].end->weight = w;
	g->adj[u].end->next = NULL;
}

void removeEdge(Graph* g, int u, int v, int w) {
	if (u >= g->qttVertex || v >= g->qttVertex) return;

	bool found = false;;	
	EdgeNode *prev = g->adj[u].begin;
	EdgeNode *aux = prev->next;

	while (aux != NULL && !found) {
		if (aux->v == v && w == aux->weight) {
			found = true;
			prev->next = aux->next;

			if (g->adj[u].end == aux) g->adj[u].end = prev;
			free(aux);
		} else {
			prev = aux;
			aux = aux->next;
		}
	}
}

void destroy(Graph* g) {
	for (int u = 0; u < g->qttVertex; u++) {
		EdgeNode* aux = g->adj[u].begin;
		while(aux != NULL) {
			EdgeNode* cur = aux->next;
			free(aux);
			aux = cur;
		}
	}

	free(g);
}