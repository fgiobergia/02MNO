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

void merge (int *v, int l, int r) {
	int i,j,a,*t,c;
	a = (l+r)/2;
	t = malloc ((r-l+1)*sizeof(int));
	for (i=l,j=a+1,c=0;c<(r-l+1);c++) {
		if (i<=a) {
			if (j<=r) {
				t[c]=(v[i]<=v[j])?v[i++]:v[j++];
			}
			else {
				t[c]=v[i++];
			}
		}
		else {
			t[c]=v[j++];
		}
	}
	for (i=l;i<=r;i++) {
		v[i]=t[i-l];
	}
	free (t);
}		

void mergesort (int *v, int l, int r) {
	int a;
	if (l==r) {
		return ;
	}
	a = (l+r)/2;
	mergesort (v,l,a);
	mergesort (v,a+1,r);
	merge (v,l,r);
}

void swap (int *a, int *b) {
	int tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}

int partition (int *v, int l, int r) {
	int pivot,i,j,t;
	pivot = v[r];
	for (i=l,j=r-1;;) {
		while (v[i++]<pivot);
		i--;
		while (v[j--]>pivot);
		j++;
		if (i>=j) {
			break;
		}
		swap (v+i,v+j);
	}
	swap(v+r,v+i);
	return i;
}

void quicksort (int *v, int l, int r) {
	int q;
	if (l>=r) {
		return ;
	}
	q = partition (v, l, r);
	quicksort (v,l,q-1);
	quicksort (v,q+1,r);
}

float run_time (void(*sort)(int*,int,int), int n, int m) {
	clock_t a,b;
	int i,*t;
	a = clock ();
	for (i=0;i<m;i++) {
		t = rand_array (n);
		(*sort)(t,0,n-1);
		free (t);
	}
	b = clock ();
	return (float)(b-a)/CLOCKS_PER_SEC;
}

/* usage: ./es01 <N> <M> */
int main (int argc, char *argv[]) {
	int m,n;
	if (argc!=3) {
		return 0;
	}
	n = atoi (argv[1]);
	m = atoi (argv[2]);
	printf ("N: %d, M: %d\n",n,m);
	printf ("Mergesort: %.3f\n",run_time(mergesort,n,m));
	printf ("Quicksort: %.3f\n",run_time(quicksort,n,m));
	return 0;
}

