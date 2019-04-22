#define branco 0
#define cinza 1
#define preto 2


int bfs(Graph* g, int V, int S) {
	int color[V];


	color[S] = cinza;
	Queue* q = createQueue();

	while(!emptyQueue(q)) {
		int u = frontQueue(q);
		
	}

	freeQueue(q);
}