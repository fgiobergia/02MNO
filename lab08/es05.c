#include <stdio.h>
#include <stdlib.h>

int move (int **b, int y, int x, int n, int s) {
	static int v[] = {-2,-2,-1,-1,+1,+1,+2,+2};
	static int h[] = {-1,+1,-2,+2,-2,+2,-1,+1};
	int i,c,d;
	if (n==s*s) {
		return 1;
	}
	for (i=0,c=0,d=0;i<8;i++) {
		if (y+v[i]>-1 && y+v[i]<s && x+h[i]>-1 && x+h[i]<s) {
			d++;
			if (!b[y+v[i]][x+h[i]]) {
				b[y+v[i]][x+h[i]]=n+1;
				if (move (b,y+v[i],x+h[i],n+1,s)) {
					return 1;
				}
				b[y+v[i]][x+h[i]]=0;
			}
			else {
				c++;
			}
		}
	}
	return 0;
}

int main (int argc, char *argv[]) {
	int **b,i,j,s;
	if (argc<2) {
		printf ("[!] Usage: %s <SIDE>\n",argv[0]);
		return 0;
	}
	s = atoi (argv[1]);
	b = malloc (s*sizeof(int*));
	for (i=0;i<s;i++) {
		b[i]=calloc(s,sizeof(int));
	}
	b[0][0]=1; // [0,0]: Starting position
	move(b,0,0,1,s);
	for (i=0;i<s;i++) {
		for (j=0;j<s;j++) {
			printf ("%02d ",b[i][j]);
		}
		printf ("\n");
	}
	return 0;
}

