#include <stdio.h>
#include <stdlib.h>

int check_matrix (int **m, int n, int res) {
	int i,d,*s;
	s = calloc (n+2,sizeof(int));
	for (i=0;i<n;i++) {
		for (d=0;d<n;d++) {
			s[d]+=m[i][d];
			if (i==d) {
				s[n]+=m[i][d];
			}
			if (i==n-d-1) {
				s[n+1]+=m[i][d];
			}
		}
	}
	for (i=0;i<n+2;i++) {
		if (s[i]!=res) {
			return 0;
		}
	}
	return 1;
}

void print_matrix (int **m, int n) {
	int i,d;
	for (i=0;i<n;i++) {
		for (d=0;d<n;d++) {
			printf ("%d ",m[i][d]);
		}
		printf ("\n");
	}
}

int gen_matrix (int **m, int y, int x, int n, int *v, int res, int line) {
	int i,ny,nx,new=0;
	if (y==n) {
		if (check_matrix (m,n,res)) {
			return 1;
		}
	}
	nx = (x+1==n)?0:x+1;
	if (!nx) {
		new=1;
	}
	for (i=1;i<=n*n;i++) {
		if (!v[i] && line+i<=res) {
			v[i]=1;
			m[y][x]=i;
			line += i;
			if (gen_matrix (m,y+new,nx,n,v,res,(new)?0:line)) {
				return 1;
			}
			line -= i;
			v[i]=0;
		}
	}
	return 0;
}

int main () {
	int **m,n,i,*v;
	printf ("< ");
	scanf ("%d",&n);
	m = malloc (n*sizeof(int*));
	v = calloc (n*n+1,sizeof(int));
	for (i=0;i<n;i++) {
		m[i] = calloc (n,sizeof(int));
	}
	if (gen_matrix (m,0,0,n,v,n*(n*n+1)/2,0)) {
		print_matrix (m,n);
	}
	else {
		printf ("Soluzione non trovata :(\n");
	}
	return 0;
}
