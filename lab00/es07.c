#include <stdio.h>

#define	A	5
#define	B	2

int scan (int m[A][A], int n[B][B]) {
	int i,d,j,k,c,f;
	for (i=0,c=0;i<A-B+1;i++) {
		for(d=0;d<A-B+1;d++) {
			f=1;
			for (j=0;j<B && f;j++) {
				for (k=0;k<B;k++) {
					if (m[i+j][d+k]!=n[j][k]) {
						f=0;
						break;
					}
				}
			}
			c+=f;
		}
	}
	return c;
}

int main () {
	int m[A][A],n[B][B];
	int i,d,t;

	printf ("#1\n");
	for (i=0;i<A;i++) {
		for (d=0;d<A;d++) {
			scanf ("%d",&m[i][d]);
		}
	}

	printf ("#2\n");
	for (i=0;i<B;i++) {
		for (d=0;d<B;d++) {
			scanf ("%d",&n[i][d]);
		}
	}

	t = scan (m,n);
	printf ("n contenuta in m %d volt%c.\n",t,(t==1)?'a':'e');
	return 0;
}
