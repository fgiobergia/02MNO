#include <stdio.h>
#include <stdlib.h>
#include <linux/types.h>

int binary_digits (__u8 v[], int d, int n) {
	int i;
	if (d==n) {
		for (i=0;i<n;i++) {
			printf ("%d",v[i]);
		}
		printf ("\n");
		return ;
	}
	v[d]=0;
	binary_digits (v,d+1,n);
	v[d]=1;
	binary_digits (v,d+1,n);
}

int main () {
	__u8 *v;
	int n;
	printf ("< ");
	scanf ("%d",&n);
	v = malloc (n);
	binary_digits (v,0,n);
	free (v);
	return 0;
}

