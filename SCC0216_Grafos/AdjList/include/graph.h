#include <stdbool.h>

#define MAXV 100

typedef int elem;
typedef struct Graph Graph;

Graph* graph_create(size_t qttVertex, bool* error);
