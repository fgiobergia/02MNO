#include <stdio.h>
#include <stdlib.h>

void read_rc (int x[2]) {
	do {
		printf ("ROWS x COLS: ");
		scanf ("%d %d",&x[0],&x[1]);
	} while (x[0]<=0 || x[1]<=0);
}

float **get_matrix (int x[2]) {
	float **m;
	int i,d;
	m = malloc (x[0]*sizeof(float*));
	printf ("Inserisci la matrice: \n");
	for (i=0;i<x[0];i++) {
		m[i] = malloc (x[1]*sizeof(float));
		for (d=0;d<x[1];d++) {
			scanf ("%f",&m[i][d]);
		}
	}
	return m;
}

float **mul_matrix (float **m1, float **m2, int s1[2], int s2[2]) {
	int i,d,j,k;
	float **p;
	if (s1[1]!=s2[0]) {
		return NULL; // mxn nxp required
	}
	p = malloc (s1[0]*sizeof(float*));
	for (i=0;i<s1[0];i++) {
		p[i]=malloc(s2[1]*sizeof(float));
		for (d=0;d<s2[1];d++) {
			p[i][d]=0;
			for (k=0,j=0;k<s1[1];k++,j++) {
				p[i][d] += (m1[i][k]*m2[j][d]);
			}
		}
	}
	return p;
}

void display_matrix (float **m, int r, int c) {
	int i,d;
	for (i=0;i<r;i++) {
		for (d=0;d<c;d++) {
			printf ("% 3f ",m[i][d]);
		}
		printf ("\n");
	}
}

int main () {
	int a[2],b[2];
	float **ma, **mb, **mc;
	read_rc (a);
	read_rc (b);

	ma = get_matrix (a);
	mb = get_matrix (b);
	display_matrix (mb,b[0],b[1]);
	 

	mc = mul_matrix (ma, mb, a, b);

	if (mc != NULL) {
		display_matrix (mc, a[0], b[1]);
		free (mc);
	}
	else {
		printf ("Error message!\n");
	}
	free (ma);
	free (mb);
	return 0;
}
	
