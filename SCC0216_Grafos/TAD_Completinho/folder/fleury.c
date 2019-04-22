/** Depth-First search on the graph. */
void graph_dfs(Graph* g, int u, bool* vis) {
	vis[u] = true;

	for (int v = 0; v < g->nVertex; v++) {
		if (g->mat[u][v] != EMPTY && vis[v] == false) {
			graph_dfs(g, v, vis);
		}
	}
}

/** Returns whether an edge u-v is a bridge. */
bool graph_isBridge(Graph* g, int u, int v, Error* error) {
	void* old = malloc(g->elemSize);
	memcpy(old, g->mat[u][v], g->elemSize);

	graph_removeEdge(g, u, v, error);
	if (!g->directed) {
		graph_removeEdge(g, v, u, error);
	}

	bool ans = false;

	bool* vis = calloc(g->nVertex, sizeof(bool));

	int start = 0;
	for (; start < g->nVertex; start++) {
		if (graph_degreeOfVertex(g, start, error) != 0)
			break;
	}

	graph_dfs(g, start, vis);

	for (int i = 0; i < g->nVertex; i++) {
		if (graph_degreeOfVertex(g, i, error) != 0 && !vis[i]) {
			ans = true;
		}
	}

	free(vis);

	graph_addEdge(g, u, v, old, error);
	graph_addEdge(g, v, u, old, error);

	free(old);

	return ans;
}

/** Returns the number of edges on a graph */
int graph_qttEdges(Graph* g, Error* error) {
	if (g == NULL) {
		error->occurred = true;
		strcpy(error->msg, "The graph is null.");
		return 0;
	}

	error->occurred = false;

	int ans = 0;
	for (int u = 0; u < g->nVertex; u++) {
		for (int v = 0; v < g->nVertex; v++) {
			if (g->mat[u][v] != EMPTY) {
				ans++;
			}
		}
	}

	return ans;
}

/** Executes the fleury algorithm to find the Eulerian Circuit of a graph. */
void graph_fleury(Graph* g, int u, int** circuit, int* circuitSize, Error* error) {

	int v = -1;

	if (graph_degreeOfVertex(g, u, error) == 1) {
		v = graph_nextAdj(g, u, 0, error);
	} else {
		v = 0;
		do {
			v = graph_nextAdj(g, u, v+1, error);
		} while (graph_isBridge(g, u, v, error));

	}

	graph_removeEdge(g, u, v, error);

	if (!g->directed) {
		graph_removeEdge(g, v, u, error);
	}

	(*circuitSize)++;
	*circuit = realloc(*circuit, (*circuitSize) * sizeof(int));
	((*circuit)[(*circuitSize)-1]) = v;


	if (graph_qttEdges(g, error) > 0)
		graph_fleury(g, v, circuit, circuitSize, error);
}

/** Checks and fill the eulerian circuit if possible. */
void graph_eulerianCircuit(Graph* g, int** circuit, int* circuitSize, Error* error) {
	if (g->directed) {
		error->occurred = true;
		strcpy(error->msg, "The fleury algorithm only works with bidirected graphs.");
		return;
	}

	error->occurred = false;

	/* Creates a copy of g */
	Graph* g2 = graph_copy(g, error);
	if (error->occurred) {
		graph_destroy(g2, error);

		error->occurred = true;
		strcpy(error->msg, "Error on creating a copy of the graph");

		*circuit = NULL;
		*circuitSize = 0;
		return;
	}

	/* Check the existence conditions. */
	int v1 = -1;
	for (int u = 0; u < g2->nVertex; u++) {
		int deg = graph_degreeOfVertex(g2, u, error);
		if (deg%2 != 0) {
			*circuitSize = 0;
			return;
		}

		if (deg != 0 && v1 == -1) {
			v1 = u;
		}
	}

	(*circuitSize)++;
	*circuit = realloc(*circuit, (*circuitSize) * sizeof(int));
	((*circuit)[(*circuitSize)-1]) = v1;

	graph_fleury(g2, v1, circuit, circuitSize, error);

	graph_destroy(g2, error);
}