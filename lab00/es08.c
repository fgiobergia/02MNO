#include <stdio.h>
#include <string.h>

#define	NSTRING	100
#define	STRLEN	20

void str_bubble_sort_rev (char m[NSTRING][STRLEN], int l, int a[NSTRING]) {
	int i,j,tmp;
	for (i=0;i<l-1;i++) {
		for (j=0;j<l-i-1;j++) {
			if (strcmp(m[a[j]],m[a[j+1]])==-1) {
				tmp=a[j];
				a[j]=a[j+1];
				a[j+1]=tmp;
			}
		}
	}
	return ;
}

int main (int argc, char *argv[]) {
	char m[NSTRING][STRLEN];
	int i,d,v[NSTRING];
	for (i=0;i<NSTRING;i++) {
		printf ("< ");
		fgets (m[i],sizeof(m[i]),stdin);
		if (strlen(m[i])==1) {
			break;
		}
		m[i][strlen(m[i])-1]=0;
	}
	for(d=0;d<i;d++) {
		v[d]=d;
	}
	str_bubble_sort_rev(m,i,v);
	for (d=0;d<i;d++) {
		printf ("> %s\n",m[v[d]]);
	}
	return 0;
}
