#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <limits.h>

#define MAX	INT_MAX/2

int *rand_array (int n) {
	int *a;
	int i;
	srand (time (NULL));
	a = malloc (n*sizeof(int));
	for (i=0;i<n;i++) {
		a[i]=rand()%MAX;
	}
	return a;
}

void insertion_sort (int *x, int n) {
	int i,j,t;
	for (i=1;i<n;i++) {
		t = x[i];
		for (j=i-1;j>=0 && x[j]>t;j--) {
			x[j+1]=x[j];
		}
		x[j+1]=t;
	}
	return ;
}

void selection_sort (int *x, int n) {
	int i,j,t,s;
	for (i=0;i<n-1;i++) {
		s=i;
		for (j=i+1;j<n;j++) {
			if (x[j]<x[s]) {
				s=j;
			}
		}
		t=x[s];
		x[s]=x[i];
		x[i]=t;
	}
	return ;
}

void bubble_sort (int *x, int n) {
	int i,j,t;
	for (i=n-1;i>=1;i--) {
		for (j=0;j<i;j++) {
			if (x[j]>x[j+1]) {
				t=x[j];
				x[j]=x[j+1];
				x[j+1]=t;
			}
		}
	}
	return ;
}
				

float run_time (void(*sort)(int*,int), int *x, int n, int m) {
	clock_t a,b;
	int i,*t;
	t = malloc (n*sizeof(int));
	a = clock ();
	for (i=0;i<m;i++) {
		memcpy (t,x,n*sizeof(int));
		(*sort)(t,n);
	}
	b = clock ();
	free (t);
	return (float)(b-a)/CLOCKS_PER_SEC;
}

/* usage: ./es01 <N> <M> */
int main (int argc, char *argv[]) {
	int *x,m,n;
	if (argc!=3) {
		return 0;
	}
	n = atoi (argv[1]);
	m = atoi (argv[2]);
	x = rand_array (n);
	printf ("N: %d, M: %d\n",n,m);
	printf ("Insertion sort: %.3f\n",run_time(insertion_sort,x,n,m));
	printf ("Selection sort: %.3f\n",run_time(selection_sort,x,n,m));
	printf ("Bubble sort:    %.3f\n",run_time(bubble_sort,x,n,m));
	return 0;
}

