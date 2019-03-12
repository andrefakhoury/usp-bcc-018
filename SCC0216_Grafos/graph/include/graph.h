#include <stdbool.h>

#define NOEDGE 0
typedef struct graph Graph;
typedef int elem;

Graph* createGraph(int* n, bool* error);
void destroyGraph(Graph* g);
void addEdge(Graph* g, int* u, int* v, elem* w, bool* error);
void removeEdge(Graph* g, int* u, int* v, bool* error);
bool checkEdge(Graph* g, int* u, int* v);
int dist(Graph* g, int* u, int* v);
void printGraph(Graph* g);
void transposeGraph(Graph* g, bool* error);
Graph *genTranspostGraph(Graph* g, bool* error);
bool emptyAdjList(Graph* g, int* u, bool* error);
int firstAdjList(Graph* g, int* u, bool* error);
void smallestEdge(Graph* g, int* u, int* v, bool* error);
int** vertexByDegree(Graph* g, bool* error);