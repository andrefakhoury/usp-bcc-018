#include "graph.h"

typedef struct EdgeNode {
	int v;
	elem weight;
	struct EdgeNode *next;
};

typedef stuct {
	EdgeNode *begin, *end;
} VertexNode;

struct Graph {
	vertexNode adj[MAXV];
	size_t qttVertex;
};

Graph* graph_create(size_t qttVertex, bool* error) {
	if (qttVertex >= MAXV) {
		*error = true;
		return NULL;
	}

	Graph* g = malloc(sizeof(Graph));
	if (!g) {
		*error = true;
		return NULL;
	}
	
	*error = false;
	g->qttVertex = qttVertex;
	for (int i = 0; i < qttVertex; i++) {
		g->adj[i].begin = malloc(sizeof(EdgeNode));
		g->adj[i].begin->weigth = 0;
		g->adj[i].begin->next = NULL;
		g->adj[i].end = g->adj[i].begin;
	}

	return g;
}

void addEdge(Graph* g, int u, int v, int w, bool* error) {
	if (u >= g->qttVertex || v >= g->qttVertex) {
		*error = true;
		return;
	} 

	*error = false;
	g->adj[u].fim->next = malloc(sizeof(EdgeNode));
	g->adj[u].fim = g->adj[u].fim->next;
	g->adj[u].fim->v = v;
	g->adj[u].fim->weight = w;
	g->adj[u].fim->next = NULL;
}

void removeEdge(Graph* g, int u, int v, int w, bool* error) {
	if (u >= g->qttVertex || v >= g->qttVertex) {
		*error = true;
		return;
	}

	*error = false;
	bool found = false;;	
	EdgeNode *prev = g->adj[u].begin;
	EdgeNode *aux = prev->next;

	while (aux != NULL && !found) {
		if (aux->v == v2) {
			found = true;
			w = aux->weight;
			prev->next = aux->next;

			if (g->adj[u].end == aux) g->adj[u].fim = prev;
			free(aux);
		} else {
			prev = aux;
			aux = aux->next;
		}
	}
}