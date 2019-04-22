#define MAXN 100

typedef int elem;
typedef struct Graph Graph;

Graph* createGraph(int V);
void destroyGraph(Graph* g);
int addEdge(Graph* g, int u, int v, elem w);
int removeEdge(Graph* g, int u, int v);
int edgeIsSet(Graph* g, int u, int v);
int degreeOfVertex(Graph* g, int u);