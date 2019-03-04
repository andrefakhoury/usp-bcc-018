#include "graph.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct node {
	int val;
	struct node** adj;
	int qttAdj;
} Node;

struct graph {
	Node** nodes;
	int size;
};

Graph* createGraph(int n) {
	Graph* g = malloc(sizeof(Graph));

	g->nodes = malloc(n * sizeof(Node*));
	for (int i = 0; i < n; i++) {
		g->nodes[i] = malloc(sizeof(Node));
		g->nodes[i]->val = i;
		g->nodes[i]->adj = NULL;
		g->nodes[i]->qttAdj = 0;
	}

	return g;
}

void addEdge(Graph* g, int st, int en) {
	Node* u = g->nodes[st];
	Node* v = g->nodes[en];

	u->qttAdj++;
	u->adj = realloc(u->adj, u->qttAdj * sizeof(Node*));
	u->adj[u->qttAdj-1] = v;
}

void print(Graph* g, int root) {
	Node* u = g->nodes[root];

	while (1) {
		printf("%d ", u->val);

		if (u->qttAdj == 0) break;
		u = u->adj[0];
	}

	printf("\n");
}

int dfs(Graph* g, Node* u, Node* dest) {
	if (u == dest) return 0;
	if (u->qttAdj == 0) return -999999;

	int ret = -999999;
	for (int i = 0; i < u->qttAdj; i++) {
		int cur = dfs(g, u->adj[i], dest);
		if (cur >= 0) {
			ret = cur;
			break;
		}
	}

	return 1 + ret;
}

int dist(Graph* g, int i, int j) {
	Node* u = g->nodes[i];
	Node* v = g->nodes[j];

	int ret = dfs(g, u, v);
	if (ret >= 0) return ret;
	else return -1;
}