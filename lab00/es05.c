#include <stdio.h>

#define	MAX	16

int main () {
	int i,a[MAX];
	printf ("< ");
	for (i=MAX-1;i>=0;i--) {
		scanf ("%d",&a[i]);
	}
	for (i=0;i<MAX;i++) {
		if (a[i]) {
			printf ("%d ",a[i]);
		}
	}
	printf ("\n");
	return 0;
}
