#include <stdio.h>
#include <stdlib.h>

#define	IN1	"input1.txt"
#define	IN2	"input2.txt"

struct matrix {
	int **m;
	int rows;
	int cols;
};

void read_matrix (char *file, struct matrix *m) {
	FILE *fp;
	int i,d;
	char line[1024];

	fp = fopen (file, "r");
	fgets (line,sizeof(line),fp);
	sscanf (line, "%d %d",&m->rows,&m->cols);
	m->m = malloc (m->rows*sizeof(int*));
	for (i=0;i<m->rows;i++) {
		m->m[i]= malloc (m->cols*sizeof(int));
		for (d=0;d<m->cols;d++) {
			fscanf (fp, "%d", &m->m[i][d]);
		}
	}
	fclose (fp);
}

void mul_matrix (struct matrix m, struct matrix n, struct matrix *p) {
	int i,d,j,k;
	p->rows = m.rows;
	p->cols = n.cols;
	p->m = malloc (p->rows*sizeof(int*));
	for (i=0;i<p->rows;i++) {
		p->m[i] = calloc (p->cols,sizeof(int));
		for (d=0;d<p->cols;d++) {
			for (k=0;k<m.cols;k++) {
				p->m[i][d] += m.m[i][k]*n.m[k][d];
			}
		}
	}
}

void print_matrix (struct matrix m) {
	int i,d;
	for (i=0;i<m.rows;i++) {
		for (d=0;d<m.cols;d++) {
			printf ("% 5d ",m.m[i][d]);
		}
		printf ("\n");
	}
}

void free_matrix (struct matrix m) {
	int i;
	for (i=0;i<m.rows;i++) {
		free (m.m[i]);
	}
	free (m.m);
}

int main () {
	struct matrix m,n,p;
	read_matrix (IN1,&m);
	read_matrix (IN2,&n);
	if (m.cols != n.rows) {
		printf ("Impossibile effettuare il prodotto :(\n");
		return 0;
	}
	mul_matrix (m,n,&p);
	print_matrix(p);

	free_matrix (m);
	free_matrix (n);
	free_matrix (p);
	return 0;
}

