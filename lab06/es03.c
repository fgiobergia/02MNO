#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define	INPUT	"input.txt"

int det (int ***n, int l, int t) {
	int i,d,j,dt,k,c;
	for (i=0;i<t;i++) {
		for (d=0;d<t;d++) {
			if (!n[i][d][1]) {
				break;
			}
		}
		if (d!=t) {
			break;
		}
	}
	if (l==1) {
		return n[i][d][0];
	}
	for (j=0,dt=0,c=1;j<t;j++) {
		if (!n[i][j][1]) {
			for (k=0;k<t;k++) {
				n[i][k][1]++;
				n[k][j][1]++;
			}
			n[i][j][1]--;
			dt += c*n[i][j][0]*det(n,l-1,t);
			for (k=0;k<t;k++) {
				n[i][k][1]--;
				n[k][j][1]--;
			}
			n[i][j][1]++;
			c *= -1;
		}
	}
	return dt;
}

int main () {
	int ***n,i,l,d;
	FILE *fp;
	char line[128];
	fp = fopen (INPUT,"r");
	for (l=0;fgets(line,sizeof(line),fp);l++);
	rewind (fp);
	n = malloc (l*sizeof(int**));
	for (i=0;i<l;i++) {
		n[i]=malloc(l*sizeof(int*));
		for (d=0;d<l;d++) {
			n[i][d]=malloc(2*sizeof(int));
			fscanf (fp,"%d",&n[i][d][0]);
			n[i][d][1]=0;
		}
	}
	printf ("%d\n",det (n,l,l));
}
