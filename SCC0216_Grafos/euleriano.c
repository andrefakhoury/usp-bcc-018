#include <stdio.h>
#include <stdlib.h>


typedef struct vector {
	
} vector;

typedef struct graph {
	node** nodes;
} graph;

typedef struct node {
	int val;
	node** next;
} node;

graph createGraph(int V) {
	graph G;

	G.nodes = malloc(V * sizeof(node*));

	return G;
}

void addEdge(graph* G, int u, int v) {
	G.nodes[u]
}