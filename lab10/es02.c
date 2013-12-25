#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define	N	3
#define	IN	"input.txt"

typedef struct {
	char *word;
	int len;
	int used;
} *Word;

int max;
char *strm;

int can_use (Word w, char *cat, int len) {
	return ((w->used < N && w->word[0]==cat[len-2] && w->word[1]==cat[len-1]) || !len);
}

void find_max (Word *w, int n, int cur, char *cat) {
	int i,j,c;
	for (i=0,c=0;i<n;i++) {
		if (can_use (w[i],cat,cur)) {
			c = 1;
			w[i]->used++;
			if (cur) {
				for (j=2;j<w[i]->len;j++) {
					cat[cur+j-2]=w[i]->word[j];
				}
				find_max (w,n,cur+w[i]->len-2,cat);
			}
			else {
				for (j=0;j<w[i]->len;j++) {
					cat[cur+j]=w[i]->word[j];
				}
				find_max (w,n,cur+w[i]->len,cat);
			}
			w[i]->used--;
		}
	}
	if (!c) {
		if (cur>max) {
			max = cur;
			strm = strndup(cat,max);
		}
	}
}

int main () {
	int i,mlen,len;
	char line[256],*str;
	FILE *fp;
	Word *w;

	fp = fopen (IN, "r");
	fgets (line,sizeof(line),fp);
	len = atoi (line);
	w = malloc (len*sizeof(Word));
	
	i=0;
	while (fgets(line,sizeof(line),fp)) {
		w[i] = malloc(sizeof(*w[i]));
		w[i]->len = strlen(line)-1;
		w[i]->used = 0;
		w[i]->word = strndup (line,w[i]->len);
		mlen += w[i]->len*N;
		i++;
	}
	str = malloc(mlen);
	find_max (w,len,0,str);
	printf ("max: %d\n%s\n",max,strm);
	return 0;
}
