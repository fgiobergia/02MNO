#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define	IN	"in3.txt"
#define	OUT	"out3.txt"

int **get_matrix (FILE *fp, int rows, int cols) {
	int i,d,**m;
	char line[512],*tmp;
	i = 0;
	m=malloc(rows*sizeof(int*));
	while (fgets (line,sizeof(line),fp)) {
		m[i]=malloc(cols*sizeof(int));
		tmp = line;
		for (d=0;d<cols;d++) {
			sscanf (tmp,"%d",&m[i][d]);
			tmp = strchr(tmp,' ')+1;
		}
		i++;
	}
	return m;
}

float **calc (int **m, int rows, int cols) {
	int i,d,j,k,c;
	float **n;
	n=malloc(rows*sizeof(float*));
	for (i=0;i<rows;i++) {
		n[i]=malloc(cols*sizeof(float));
		for (d=0;d<cols;d++) {
			n[i][d]=-m[i][d];
			for (j=i-1,c=-1;j<=i+1;j++) {
				for (k=d-1;k<=d+1;k++) {
					if (j>-1 && k>-1 && j<rows && k<cols) {
						c++;
						n[i][d]+=m[j][k];
					}
				}
			}
			n[i][d]/=c;
		}
	}
	return n;
}

void print_out (float **m, int rows, int cols) {
	FILE *fp;
	int i,d;
	fp = fopen (OUT,"w");
	fprintf (fp, "%d %d\n",rows,cols);
	for (i=0;i<rows;i++) {
		for (d=0;d<cols;d++) {
			fprintf (fp, "%.1f ",m[i][d]);
		}
		fprintf(fp,"\n");
	}
	fclose (fp);
}

int main () {
	FILE *fp;
	char line[16];
	int c,r,**m,i;
	float **n;
	fp = fopen (IN,"r");
	fgets (line,sizeof(line),fp);
	sscanf (line,"%d %d",&r,&c);
	m=get_matrix (fp,r,c);
	n=calc (m,r,c);
	print_out (n,r,c);
	fclose(fp);
	for (i=0;i<r;i++) {
		free(m[i]);
		free(n[i]);
	}
	free(m);
	free(n);
	return 0;
}

