#include "Graph.h"

Graph NewGraph (int v) {
	Graph g;
	int i;
	g = malloc (sizeof(*g));
	g->v = v;
	g->l = malloc (g->v*sizeof(int*));
	for (i=0;i<g->v;i++) {
		g->l[i] = calloc (g->v,sizeof(int));
	}
	return g;
}

void NewEdge (Graph g, int n1, int n2) {
	g->l[n1][n2] = 1;
}

int *GraphNodeLinks (Graph g, int n) {
	return g->l[n];
}

int GraphNodesNumber (Graph g) {
	return g->v;
}

