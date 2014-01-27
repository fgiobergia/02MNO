#include <stdio.h>
#include "Table.h"
#include "Graph.h"

int get_w (int a, int b, void *v) {
	int w;
	Table t = (Table)v;
	printf ("Weight for [%s->%s]? ",TableGetValue(t,a),TableGetValue(t,b));
	scanf ("%d",&w);
	return w;
}

void print_e (int a, int b, int w, void *v) {
	Table t = (Table)v;
	printf ("%s <---(%d kbps)---> %s\n",TableGetValue(t,a),w,TableGetValue(t,b));
}

void print_bridge (int a, int b, void *v) {
	Table t = (Table)v;
	printf ("Bridge: %s <-> %s\n",TableGetValue(t,a),TableGetValue(t,b));
}

int main () {
	Graph g;
	Table t;
	FILE *fp;
	int n = 13,w,v[2];
	char line[128],n1[64],n2[64];
	t = NewTable (n,16);
	g = NewGraph (n);
	fp = fopen ("input.txt","r");
	while (fgets(line,sizeof(line),fp)) {
		sscanf (line,"%64s %64s %d",n1,n2,&w);
		v[0] = TableGetId(t,n1);
		if (v[0]<0) {
			v[0] = TableNewValue(t,n1);
		}
		v[1] = TableGetId(t,n2);
		if (v[1]<0) {
			v[1] = TableNewValue (t,n2);
		}
		NewEdge (g,v[0],v[1],w);
	}
	line[0] = 0;
	while (line[0]!='q') {
		fgets(line,sizeof(line),stdin);
		switch (line[0]) {
			case 'k':
				if (GraphIsConnected(g)) {
					printf ("The graph is connected\n");
				}
				else {
					printf ("The graph is NOT connected\n");
				}
				break;
			case 'c':
				ConnectGraph (g,get_w,t);
				printf ("The graph is now connected\n");
				break;
			case 'r':
				sscanf (line+1,"%64s",n1);
				v[0] = TableGetId(t,n1);
				RemoveNode(g,v[0]);
				printf ("Node '%s' removed\n",n1);
				break;
			case 'n':
				sscanf (line+1,"%64s %64s %d",n1,n2,&w);
				v[0] = TableGetId(t,n1);
				if (v[0]<0) {
					v[0] = TableNewValue(t,n1);
				}
				v[1] = TableGetId(t,n2);
				if (v[1]<0) {
					v[1] = TableNewValue (t,n2);
				}
				NewEdge (g,v[0],v[1],w);
				printf ("New edge added\n");
				break;
			case 'b':
				GetBridgesList(g,print_bridge,get_w,t);
				break;
			case 'd':
				DisplayGraph (g,print_e,t);
				break;
			case 'h':
				printf ("k\t\t\tchecK if the graph is connected\n"
				        "c\t\t\tConnect graph\n"
					"r <node>\t\tRemove 'node'\n"
					"n <n1> <n2> <w>\tAdd an edge from 'n1' to 'n2' weighted 'w'\n"
					"b\t\t\tDisplay a list of bridges\n"
					"d\t\t\tDisplay graph\n"
					"h\t\t\tDisplay this message\n"
					"q\t\t\tExit\n");
				break;
			defualt:
				break;
		}
	}
	return 0;
}

