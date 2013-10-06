#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define	N	6

struct date {
	int y;
	int m;
	int d;
	int j;
} date;

void bubble_sort_dates (struct date *t, int flag) {
	int i,j;
	struct date tmp;
	for (i=0;i<N-1;i++) {
		for (j=0;j<N-i-1;j++) {
			if ((t[j].j>t[j+1].j && flag) || (t[j].j<t[j+1].j && !flag)) {
				tmp=t[j];
				t[j]=t[j+1];
				t[j+1]=tmp;
			}
		}
	}
}

int main () {
	char fname[64],line[16];
	FILE *fp;
	struct date *t;
	int i,flag;
	t = malloc (N*sizeof(struct date));
	printf ("< ");
	fgets (fname,sizeof(fname),stdin);
	fname[strlen(fname)-1]=0;
	printf ("< ");
	scanf ("%d",&flag);
	fp = fopen (fname,"r");
	i = 0;
	while (fgets (line,sizeof(line),fp)) {
		sscanf (line,"%d-%d-%d",&t[i].d,&t[i].m,&t[i].y);
		t[i].j = t[i].y*10000+t[i].m*100+t[i].d;
		i++;
	}
	fclose (fp);
	bubble_sort_dates (t,flag);
	for (i=0;i<N;i++) {
		printf ("%02d-%02d-%04d\n",t[i].d,t[i].m,t[i].y);
	}
	free (t);
	return 0;
}
