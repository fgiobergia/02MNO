#include <stdio.h>
#include "Graph.h"
#include "Table.h"

/*
 * The input file contains, on the
 * first line, the number of airports.
 * The following lines contain every
 * flight's infos.
 */
#define	IN	"input.txt"

void visit_graph (Graph g, int origin, int node, int *visited, Table t) {
	int *l,i;
	l = GraphNodeLinks(g,node);
	for (i=0;i<GraphNodesNumber(g);i++) {
		if (l[i] && !visited[i]) {
			printf ("Visited %s",TableGetString(t,i));
			visited[i]=1;
			if (i == origin) {
				printf (" (loop)\n");
			}
			else {
				printf("\n");
				visit_graph(g,origin,i,visited,t);
			}
		}
	}
}

int main () {
	FILE *fp;
	char line[128],str[2][32];
	Table t;
	Graph g;
	int i,cities,d,id[2],*v;

	fp = fopen (IN,"r");
	fgets (line,sizeof(line),fp);
	cities = atoi (line);
	t = NewTable(cities,32);
	g = NewGraph (cities);
	while (fgets(line,sizeof(line),fp)) {
		sscanf (line,"%s %s",str[0],str[1]);
		for (i=0;i<2;i++) {
			id[i]=TableGetId(t,str[i]);
			if (id[i]<0) {
				id[i] = TableAddValue(t,str[i]);
			}
		}
		NewEdge (g,id[0],id[1]);
	}

	printf ("< ");
	scanf ("%32s",str[0]);
	id[0] = TableGetId(t,str[0]);
	v = calloc(cities,sizeof(int));
	visit_graph (g,id[0],id[0],v,t);
	return 0;
}

