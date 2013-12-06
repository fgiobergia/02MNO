#include <stdio.h>
#include <stdlib.h>

void merge (int *v, int l, int r, int *c) {
	int i,j,a,*b,d,t;
	a = (l+r)/2;
	b = malloc ((r-l+1)*sizeof(int));
	for (i=l,j=a+1,d=0;d<(r-l+1);d++) {
		if (i<=a && j<=r && v[i]>v[j]) {
			#ifdef LIST
				for (t=i;t<=a;t++) {
					printf ("(%d, %d)\n",v[t],v[j]);
				}
			#endif
			*c += a-i+1;
		}
		b[d]=((i<=a)?(j<=r)?(v[i]>v[j])?v[j++]:v[i++]:v[i++]:v[j++]);
	}
	for (i=l;i<=r;i++) {
		v[i]=b[i-l];
	}
	free (b);
}		

void count (int *v, int l, int r, int *c) {
	int a,p;
	if (l>=r) {
		return ;
	}
	a = (l+r)/2;
	count (v,l,a,c);
	count (v,a+1,r,c);
	merge (v,l,r,c);
}

void usage (char *name) {
	fprintf (stderr, "[!] Usage: %s <N>\n",name);
}

int main (int argc, char *argv[]) {
	int c,i,n;
	int *v;
	if (argc<2) {
		usage (argv[0]);
		return 0;
	}
	n = atoi (argv[1]);
	v = malloc (n*sizeof(int));
	for (i=0;i<n;i++) {
		printf ("v[%d] < ",i);
		scanf ("%d",&v[i]);
	}
	c=0;
	count (v,0,n-1,&c);
	printf ("> %d\n",c);
	free (v);
	return 0;
}
