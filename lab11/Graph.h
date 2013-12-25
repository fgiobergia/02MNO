#include <stdlib.h>

typedef struct {
	int **l;
	int v;
} *Graph;

Graph NewGraph (int);
void NewEdge (Graph, int, int);
int *GraphNodeLinks (Graph, int);
int GraphNodesNumber (Graph);
