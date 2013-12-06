#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void next (int **sudoku, int i, int d, int *j, int *k, int side) {
	int y,x;
	for (y=i;y<side;y++) {
		for (x=(y==i)?d+1:0;x<side;x++) {
			if (!sudoku[y][x]) {
				*j = y;
				*k = x;
				return ;
			}
		}
	}
	*j = -1;
}

int valid (int **sudoku, int i, int d, int n, int side) {
	int j,k,y,x,v;
	v = (int)(sqrt((float)side));
	y = v*(i/v);
	x = v*(d/v);
	for (j=0;j<side;j++) {
		if (sudoku[i][j]==n || sudoku[j][d]==n || sudoku[y+j/v][x+j%v]==n) {
			return 0;
		}
	}
	return 1;
}

int next_number (int **sudoku, int i, int d, int side) {
	int j,k,n;
	next (sudoku,i,d,&j,&k,side);
	if (j<0) {
		for (j=0;j<side;j++) {
			for (k=0;k<side;k++) {
				printf ("%d ",sudoku[j][k]);
			}
			printf("\n");
		}
		return 1;
	}
	for (n=1;n<=side;n++) {
		if (valid (sudoku,j,k,n,side)) {
			sudoku[j][k]=n;
			if (next_number(sudoku,j,k,side)) {
				return 1;
			}
			sudoku[j][k]=0;
		}
	}
	return 0;
}

int main (int argc, char *argv[1]) {
	int **v,i,n,d;
	FILE *fp;
	char line[256];
	fp = fopen ("sudoku.txt","r");
	fgets (line,sizeof(line),fp);
	n = atoi (line);
	v = malloc (n*sizeof(int*));
	for (i=0;i<n;i++) {
		v[i]=malloc(n*sizeof(int));
		for (d=0;d<n;d++) {
			fscanf (fp, "%d", &v[i][d]);
		}
	}
	fclose (fp);
	next_number(v,0,-1,n);
	return 0;
}
