#include <stdbool.h>

#define MAXV 100

typedef int elem;
typedef struct Graph Graph;

Graph* graph_create(size_t qttVertex, bool* error);
void addEdge(Graph* g, int u, int v, int w, bool* error);
void removeEdge(Graph* g, int u, int v, int w, bool* error);