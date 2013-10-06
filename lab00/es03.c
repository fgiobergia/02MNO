#include <stdio.h>
#define	N	20

#define	R	5
#define	C	5 // 2n+3

void enum_white (int m[N][N], int y, int x) {
	int i,d,c;
	for (i=0,c=1;i<y;i++) {
		for (d=0;d<x;d++) {
			if (m[i][d]<0) {
				if ((!d || !m[i][d-1]) && (d+1<x && m[i][d+1])) {
					m[i][d]=c++;
				}
				else if ((!i || !m[i-1][d]) && (i+1<y && m[i+1][d])) {
					m[i][d]=c++;
				}
			}
		}
	}
}

void display (int m[N][N], int y, int x) {
	int i,d,k,j;
	for (i=0;i<=y;i++) {
		for (k=0;k<(C+1)*x+1;k++) {
			printf ("-");
		}
		printf ("\n");
		if (i==y) {
			break;
		}
		for (j=0;j<R;j++) {
			for (d=0;d<x;d++) {
				printf ("|");
				if (m[i][d]<1 || j) {
					for (k=0;k<C;k++) {
						printf ("%c",m[i][d]?' ':'*');
					}
				}
				else {
					for (k=0;k<(C-3)/2;k++) {
						printf (" ");
					}
					printf ("% 3d",m[i][d]);
					for (k=0;k<(C-3)/2;k++) {
						printf (" ");
					}
				}
			}
			printf ("|\n");
		}
	}

}

int main () {
	int c[N][N],i,d;
	FILE *fp;
	char tmp[N+1],name[256];
	do {
		printf ("< ");
		scanf ("%s",name);
		fp = fopen (name,"r");
	} while (fp==NULL);
	i=0;
	while (fgets (tmp,sizeof(tmp),fp)) {
		for (d=0;(tmp[d]=='0' || tmp[d]=='1');d++) {
			c[i][d]=tmp[d]-49;
			// -1: bianca
			// 0 : nera

		}
		i++;
	}
	enum_white(c,i,d);
	display (c,i,d);
	return 0;
}
