#include <stdio.h>

#define	MAX 5

void bubble_sort (int a[MAX]) {
	int i,j,tmp;
	for (i=0;i<MAX-1;i++) {
		for (j=0;j<MAX-i-1;j++) {
			if (a[j]>a[j+1]) {
				tmp=a[j];
				a[j]=a[j+1];
				a[j+1]=tmp;
			}
		}
	}
}

int main () {
	int a[MAX],i;
	printf ("< ");
	for (i=0;i<MAX;i++) {
		scanf ("%d",&a[i]);
	}
	bubble_sort (a);
	printf ("> ");
	for (i=0;i<MAX;i++) {
		printf ("%d ",a[i]);
	}
	printf ("\n");
	return 0;
}

