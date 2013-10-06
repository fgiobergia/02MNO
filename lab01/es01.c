/* gcc -o es1 es1.c -lm */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

float **gen_matrix (FILE *fp, int n) {
	char line[1024],*tmp;
	int i,d;
	float **m,t;
	m = malloc (n*sizeof(float*));
	i=0;
	while (fgets (line,sizeof(line),fp)) {
		m[i]=malloc(n*sizeof(float));
		tmp = line;
		for (d=0;d<n;d++) {
			sscanf (tmp,"%f",&t);
			if (t<=0) {
				m[i][d]=0;
			}
			else {
				m[i][d]=pow(10,ceil(log10(t)));
			}
			tmp = strchr(tmp,' ')+1;
		}
		i++;
	}
	return m;
}

int symmetry (float **m, int n) {
	int i,d;
	for (d=0;d<n-1;d++) {
		for (i=d+1;i<n;i++) {
			if (m[i][d]!=m[d][i]) {
				return 0;
			}
		}
	}
	return 1;
}

int main () {
	char fname[64],line[16];
	int n,i;
	float **m;
	FILE *fp;
	printf ("< ");
	fgets (fname,sizeof(fname),stdin);
	fname[strlen(fname)-1]=0;
	fp = fopen (fname, "r");
	fgets (line,sizeof(line),fp);
	sscanf (line, "%d",&n);
	m = gen_matrix (fp, n);
	if (symmetry(m,n)) {
		printf ("Matrice simmetrica.\n");
	}
	else {
		printf ("Matrice non simmetrica.\n");
	}
	for (i=0;i<n;i++) {
		free (m[i]);
	}
	free(m);
	fclose (fp);
	return 0;
}

