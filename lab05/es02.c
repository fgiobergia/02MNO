#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define	INPUT	"input.txt"
#define	DIST	5

struct pt {
	float x;
	float y;
	float d;
};

struct pt *load_array (char *filename, int *len) {
	FILE *fp;
	int i,j,t,d;
	struct pt *p;
	char line[128];
	fp = fopen (filename, "r");
	t  = 1;
	i = 0;
	p = malloc (t*sizeof(struct pt));
	while (fgets (line,sizeof(line),fp)) {
		if (i>=t) {
			t *= 2;
			p = realloc (p, t*sizeof(struct pt));
		}
		sscanf (line, "%f %f",&p[i].x,&p[i].y);
		p[i].d = sqrt(pow(p[i].x,2)+pow(p[i].y,2));

		i++;
	}
	*len = i;
	fclose (fp);
	return p;
}

float dist (struct pt p1, struct pt p2) {
	return sqrt(pow(p1.x-p2.x,2)+pow(p1.y-p2.y,2));
}

void get_min_max (struct pt *p, int len) {
	int i,j,c;
	int imin[2], imax[2];
	float dmin, dmax,t;
	dmax = -1;
	dmin = -1;
	for (i=0,c=0;i<len;i++) {
		for (j=i+1;j<len;j++) {
			t = dist(p[i],p[j]);
			if (t<DIST) {
				c++;
			}
			if (t<dmin || dmin==-1) {
				dmin = t;
				imin[0]=i;
				imin[1]=j;
			}
			if (t>dmax) {
				dmax = t;
				imax[0]=i;
				imax[1]=j;
			}
		}
	}
	printf ("min: %f (%.02f %.02f ; %.02f %.02f)\n",dmin,p[imin[0]].x,p[imin[0]].y,p[imin[1]].x,p[imin[1]].y);
	printf ("max: %f (%0.2f %.02f ; %.02f %.02f)\n",dmax,p[imax[0]].x,p[imax[0]].y,p[imax[1]].x,p[imax[1]].y);
	printf ("\n# of segments: %d\n\n",c);
}

void swap (struct pt *p1, struct pt *p2) {
	struct pt t;
	t = *p1;
	*p1 = *p2;
	*p2 = t;
}

int partition (struct pt *p, int l, int r) {
	int pivot,i,j;
	pivot = p[r].d;
	for (i=l,j=r-1;;) {
		while (p[i++].d>pivot);
		i--;
		while (p[j--].d<pivot);
		j++;
		if (i>=j) {
			break;
		}
		swap (&p[i],&p[j]);
	}
	swap (&p[i],&p[r]);
	return i;
}

void quicksort (struct pt *p, int l, int r) {
	int q;
	if (l>=r) {
		return ;
	}
	q = partition (p, l, r);
	quicksort (p,l,q-1);
	quicksort (p,q+1,r);
}

int main () {
	struct pt *p;
	int len,i;
	p = load_array (INPUT,&len);
	get_min_max (p, len);
	quicksort (p,0,len-1);
	for (i=0;i<len;i++) {
		printf ("x: %.02f y: %.02f d: %0.2f\n",p[i].x,p[i].y,p[i].d);
	}
	free (p);
	return 0;
}

