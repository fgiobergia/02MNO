#include "Graph.h"

// Grafico, utilizzando una matrice delle adiacenze
Graph NewGraph (int v) {
	int i;
	Graph g;
	g = malloc (sizeof(*g));
	g->n = v;
	g->m = malloc (g->n*sizeof(int*));
	for (i=0;i<g->n;i++) {
		g->m[i] = calloc (g->n,sizeof(int));
	}
	g->active = calloc (g->n,sizeof(int));
	g->edges = calloc (g->n,sizeof(int));
	return g;
}

void NewEdge (Graph g, int a, int b, int w) {
	if (!g->m[a][b]) {
		g->edges[a]++;
		g->edges[b]++;
	}
	g->active[a] = 1;
	g->active[b] = 1;
	g->m[a][b] = w;
	g->m[b][a] = w;
}

void RemoveEdge (Graph g, int a, int b) {
	if (g->m[a][b]) {
		g->edges[a]--;
		g->edges[b]--;
	}
	g->m[a][b] = 0;
	g->m[b][a] = 0;
}

void RemoveNode (Graph g, int n) {
	int i;
	for (i=0;i<g->n;i++) {
		RemoveEdge (g,i,n);
	}
	g->active[n] = 0;
}

int IsActive (Graph g, int n) {
	return g->active[n];
}

int GetEdgesNum (Graph g, int n) {
	return g->edges[n];
}

int GraphGetFirstActive (Graph g) {
	int i;
	for (i=0;i<g->n;i++) {
		if (IsActive (g,i)) {
			return i;
		}
	}
	return -1;
}

// Depth First Search, scansiona il grafo ricorsivamente
// aggiornando v ogni volta che viene visistato un nuovo
// nodo.
void GraphDFS (Graph g, int n, int *v, int mark) {
	int i;
	for (i=0;i<g->n;i++) {
		if (g->m[n][i] && !v[i] && IsActive(g,i)) {
			v[i] = mark;
			GraphDFS(g,i,v,mark);
		}
	}
}

// Controlla con una DFS se il grafo e' connesso
int GraphIsConnected (Graph g) {
	int *v,i;
	v = calloc (g->n,sizeof(int));
	GraphDFS (g,GraphGetFirstActive(g),v,1);
	for (i=0;i<g->n;i++) {
		// Se il nodo i-esimo non contiene
		// 1 ed e' attivo, non e' raggiungibile
		if (!v[i] && IsActive(g,i)) {
			return 0;
		}
	}
	return 1;
}

// Con una serie di DFS si cercano i sottografi di un grafo
int *GraphGetSub (Graph g) {
	int *v,i,c;
	v = calloc (g->n,sizeof(int));
	for (i=0,c=1;i<g->n;i++) {
		// Se i non e' stato ancora visitato,
		// viene visitato, assegnandogli c come flag
		if (!v[i] && IsActive(g,i)) {
			v[i]=c;
			GraphDFS (g,i,v,c++);
		}
	}
	return v;
}

// swap per partition()
void swap (int **c, int a, int b) {
	int x[2],y[2];
	x[0] = c[0][a];
	x[1] = c[1][a];
	*(c[0]+a) = c[0][b];
	*(c[1]+a) = c[1][b];
	*(c[0]+b) = x[0];
	*(c[1]+b) = x[1];
}

// partition per quicksort()
int partition (int **c, int l, int r) {
	int pivot,i,j;
	pivot = c[0][r];
	for (i=l,j=r-1;;) {
		while (c[0][i++]>pivot); i--;
		while (c[0][j--]<pivot); j++;
		if (i>=j) {
			break;
		}
		swap (c, i, j);
	}
	swap (c, i, r);
	return i;
}

// quicksort ordina in ordine decrescente, 
// basandosi sulla cardinalita', i sottografi
void quicksort (int **c, int l, int r) {
	int q;
	if (l>=r) {
		return ;
	}
	q = partition (c,l,r);
	quicksort (c,l,q-1);
	quicksort (c,q+1,r);
}

// connette i sottografi di un grafo.
// Viene usata la callback 'callback()' per 
// ottenere il peso da usare per l'arco
void ConnectGraph (Graph g, int(*callback)(int,int,void*),void *param) {
	int *v,**count,i,c,w;
	v = GraphGetSub(g);
	count = malloc (2*sizeof(int*)); // 0: # di nodi, 1: nodo con max connessioni
	count[0] = calloc (g->n,sizeof(int)); // valore default: 0 (qualunque nodo ha piu' di 0 archi)
	count[1] = malloc (g->n*sizeof(int));
	// inizializza il nodo con # massimo di archi a -1
	// (per sapere in seguito il # di sottografi)
	for (i=0;i<g->n;i++) {
		count[1][i] = -1;
	}
	// scansiona il risultato di GraphGetSub.
	// Dato che la funzione ordina m sottografi
	// assegnando un valore j da 1 a m, si usa
	// j-1 come indice per 'count'
	for (i=0;i<g->n;i++) {
		// si somma 1 alla cardinalita'
		// del sottografo a cui appartiene il 
		// nodo in considerazione
		count[0][v[i]-1]++;
		// se il nodo in considerazione ha piu' archi del nodo
		// con piu' archi del sottografo, si aggiorna il nodo
		// con piu' archi
		if (count[1][v[i]-1]==-1 || GetEdgesNum(g,i)>GetEdgesNum(g,count[1][v[i]-1])) {
			count[1][v[i]-1] = i;
		}
	}
	for (c=0;c<g->n;c++) {
		if (count[1][c]<0) {
			break;
		}
	}
	quicksort (count,0,c-1);
	for (i=1;i<c;i++) {
		// si creano archi tra il sottografo di 
		// cardinalita' massima e gli altri sottografi
		w = callback(count[1][0],count[1][i],param);
		NewEdge (g,count[1][0],count[1][i],w);

	}
	return ;
}

// Elenca i ponti presenti in un grafo 
int BridgesList (Graph g, int n, int m, int *pre, int *low, int time, void(*callback_print)(int,int,void*),int(*callback_weight)(int,int,void*),void *param) {
	int i,w;
	pre[n] = time;
	low[n] = time;
	for (i=0;i<g->n;i++) {
		if (IsActive (g,i) && g->m[n][i]) {
			if (pre[i]==-1) {
				// Se BridgesList ritorna 1 (vedi dopo), si ritorna subito
				if (BridgesList (g,i,n,pre,low,time+1,callback_print,callback_weight,param)==1) {
					return 1;
				}
				if (low[n]>low[i]) {
					low[n] = low[i];
				}
				if (low[i] == pre[i]) {
					callback_print(n,i,param); // callback chiamata per visualizzare un bridge
					// se i due nodi hanno piu' di un arco, questi vengono connessi
					if (g->edges[n]>1 && g->edges[i]>1) {
						// Se il nodo che si sta visitando non e' il 
						// primo, si collega un altro nodo collegato a
						// n (m, da cui si e' raggiunto n) con i. 
						// Altrimenti (m==-1) si cerca un nodo connesso
						// a n (dato che si tratta di un nodo con piu'
						// di un arco, ne esiste almeno uno), a meno che
						// non ci siano self-loops, ma dato l'utilizzo 
						// del grafo, si assume non ce ne siano.
						// (In alternativa, si puo' incrementare (decrementare)
						// edges[v] solo quando si aggiunge (toglie) un arco
						// che non sia un self loop
						if (m==-1) {
							for (m=0;;m++) {
								if (g->m[m][n] && m!=i) {
									break;
								}
							}
						}
						w = callback_weight (m,i,param);
						NewEdge (g,m,i,w);
						if (w) {
							return 1;
						}
					}
				}
			}
			else if (i != m) {
				if (low[n] > pre[i]) {
					low[n] = pre[i];
				}
			}
		}
	}
	return 0;
}

// Front-end per BridgesList
void GetBridgesList (Graph g,void(*callback1)(int,int,void*),int(*callback2)(int,int,void*),void *param) {
	int i,*low,*pre,f;
	do {
		low = malloc (g->n*sizeof(int));
		pre = malloc (g->n*sizeof(int));
		for (i=0;i<g->n;i++) {
			pre[i]=-1;
			low[i]=-1;
		}
		f = BridgesList(g,GraphGetFirstActive(g),-1,pre,low,0,callback1,callback2,param);
		free(low);
		free(pre);
	} while (f);
}

// Viene mostrato il grafico, chiamando
// una callback specificata dall'utente
// per ogni arco presente nel grafo.
void DisplayGraph (Graph g, void(*callback)(int,int,int,void*), void *param) {
	int i,j;
	for (i=0;i<g->n;i++) {
		for (j=0;j<i;j++) {
			if (IsActive (g,i) && IsActive (g,j) && g->m[i][j]) {
				callback (i,j,g->m[i][j],param);
			}
		}
	}
}

