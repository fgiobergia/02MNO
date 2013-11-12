#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// 1 -> integer, !=1 -> string
#define	TYPE	0
#define	INPUT	"input.txt"

#if TYPE == 1

#define	EQUALS(x,y)	x==y
#define	LT(x,y)		x<y
#define	GT(x,y)		x>y
#define	ASSIGN(x,y)	x=atoi(y);

#define	ITEM_FS		"%d"
#define	ITEM_TYPE	int

#else

#define	EQUALS(x,y)	!strcmp(x,y)
#define	LT(x,y)		strcmp(x,y)<0
#define	GT(x,y)		strcmp(x,y>0
#define	ASSIGN(x,y)	x=strdup(y)

#define	ITEM_FS		"%s"
#define	ITEM_TYPE	char *

#endif

typedef ITEM_TYPE item;

int search (item *haystack, item needle, int l, int r) {
	int a;
	a = (l + r) / 2;
	if (EQUALS(haystack[a],needle)) {
		return a;
	}
	if (l>=r) {
		return -1;
	}
	if (LT(haystack[a],needle)) {
		return search (haystack, needle, a+1, r);
	}
	else {
		return search (haystack, needle, l, a-1);
	}
}

int main () {
	item *t;
	item n;
	int i,j,pos;
	FILE *fp;
	char line[64];
	fp = fopen (INPUT,"r");
	j = 1;
	i = 0;
	t = malloc (j*sizeof(item));
	while (fgets (line, sizeof(line), fp)) {
		if (i>=j) {
			j *= 2;
			t = realloc (t, j*sizeof(item));
		}
		line[strlen(line)-1]=0;
		ASSIGN(t[i],line);
		i++;
	}
	printf ("< ");
	fgets (line,sizeof(line),stdin);
	line[strlen(line)-1]=0;
	ASSIGN(n,line);
	pos = search (t,n,0,i);
	if (pos==-1) {
		printf ("Not found.\n");
	}
	else {
		printf ("Element found @ position %d\n",pos);
	}
	return 0;
}
