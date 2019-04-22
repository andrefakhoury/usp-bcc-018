typedef struct Vertex {
	int u, degree;
} Vertex;

int cmp_degree(const void* a, const void* b) {
	return -((*((Vertex*)a)).degree - (*((Vertex*)b)).degree);
}

void graph_innerWelshPowell(Graph* g, int* color, Vertex* ordV, int curColor, Error* error) {
	if (color == NULL)
		color = malloc(g->nVertex * sizeof(int));

	int u = 0;
	while (u < g->nVertex && color[ordV[u].u] != 0) u++;
	if (u == g->nVertex) return;

	u = ordV[u].u;

	color[u] = curColor;

	for (int i = 0; i < g->nVertex; i++) {
		int v = ordV[i].u;
		if (color[v] != 0) continue;

		bool flag = true;

		for (int j = 0; j < g->nVertex; j++) {
			if (g->mat[v][j] != EMPTY && color[j] == curColor) {
				flag = false;
				break;
			}
		}

		if (flag) color[v] = curColor;
	}

	graph_innerWelshPowell(g, color, ordV, curColor+1, error);
}

void graph_welshPowell(Graph* g, int* color, Error* error) {
	Vertex* vert = malloc(g->nVertex * sizeof(Vertex));

	for (int i = 0; i < g->nVertex; i++) {
		vert[i].u = i;
		vert[i].degree = graph_degreeOfVertex(g, i, error);
	}

	qsort(vert, g->nVertex, sizeof(Vertex), cmp_degree);

	graph_innerWelshPowell(g, color, vert, 1, error);

	free(vert);
}