#include <stdio.h>
#include <math.h>

#define	MAX	100
#define	OUT	"output.txt"

int main () {
	int m[MAX][MAX];
	int rows,cols,i,d;
	FILE *fp;
	printf ("< ");
	scanf ("%d",&rows);
	printf ("< ");
	scanf ("%d",&cols);

	for (i=0;i<rows;i++) {
		for (d=0;d<cols;d++) {
			if (i%2) {
				m[i][d]=(i+1)*cols-d;
			}
			else {
				m[i][d]=i*cols+d+1;
			}
		}
	}

	fp=fopen (OUT,"w");
	for (i=0;i<rows;i++) {
		for (d=0;d<cols;d++) {
			printf ("%*d ",(int)log10(rows*cols)+1,m[i][d]);
			fprintf (fp, "%*d ",(int)log10(rows*cols)+1,m[i][d]);
		}
		printf ("\n");
		fprintf(fp,"\n");
	}
	fclose(fp);
	return 0;
}


