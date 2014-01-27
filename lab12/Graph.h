#include <stdlib.h>

typedef struct {
	int **m;	// Matrice delle adiacenze
	int *active;	// Per ogni v, active[v]==1 se v e' attivp, 0 altrimenti
	int *edges;	// Per ogni v, edges[v] contiene il numero di archi che partono da v
	int n;		// numero di nodi massimi
} *Graph;

Graph NewGraph (int);
void NewEdge (Graph, int, int, int);
void RemoveNode (Graph, int);
int GraphIsConnected (Graph);
void ConnectGraph (Graph, int(*)(int,int,void*),void *);
void GetBridgesList (Graph,void(*)(int,int,void*),int(*)(int,int,void*),void *);
void DisplayGraph (Graph, void(*)(int,int,int,void*), void *);
