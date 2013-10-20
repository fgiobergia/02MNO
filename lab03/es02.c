/*
 * fatto solo con i puntatori,
 * con le stringhe decisamente
 * non ne avevo voglia :-)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define	IN	"input.txt"

void insertion_sort_string (char **a, int l) {
	char *t;
	int i,j;
	for (i=1;i<l;i++) {
		t = a[i];
		for (j=i-1;j>=0 && strcmp(a[j],t)>0;j--) {
			a[j+1]=a[j];
		}
		a[j+1]=t;
	}
	return ;
}

int main () {
	char line[32],**m;
	int i,d;
	FILE *fp;
	fp = fopen (IN, "r");
	i = 0;
	m = malloc(sizeof(char*));
	while (fgets (line,sizeof(line),fp)) {
		m = realloc (m, ++i*sizeof(char*));
		m[i-1]=malloc(strlen(line));
		strncpy (m[i-1],line,strlen(line)-1);
	}
	insertion_sort_string (m,i);
	for (d=0;d<i;d++) {
		printf ("%s\n",m[d]);
	}
	fclose (fp);
	return 0;
}

