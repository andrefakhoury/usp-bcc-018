typedef struct graph Graph;

Graph* createGraph(int n);
void addEdge(Graph* g, int u, int v);
void print(Graph* g, int root);
int dist(Graph* g, int u, int v);