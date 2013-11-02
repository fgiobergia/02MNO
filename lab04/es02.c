#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define	IN1	"input1.txt"
#define	IN2	"input2.txt"

struct word {
	char *s;
	int c;
	int *i;
	int t;
};

int is_space (char ch) {
	return (ch==' ' || ch=='\n' || ch=='\t');
}

int main () {
	FILE *fp;
	struct word *p;
	int i,d,j,cnt;
	char line[128],*ptr;

	fp = fopen (IN1,"r");
	fgets (line,sizeof(line),fp);
	sscanf (line,"%d",&d);
	p = malloc (d*sizeof(struct word));
	for (i=0;i<d;i++) {
		fgets (line,sizeof(line),fp);
		line[strlen(line)-1]=0;
		p[i].s = strdup (line); // parola
		p[i].c = 0; // numero di parole trovate
		p[i].i = malloc (sizeof (int)); // puntatore alle istanze trovate
		p[i].t = 1; // numero di int allocati dinamicamente
	}
	fclose (fp);
	
	fp = fopen (IN2,"r");
	cnt=1;
	while (fgets (line, sizeof(line), fp)) {
		for (ptr=line;;) {
			for (j=0;j<d;j++) {
				if (!strncasecmp(p[j].s,ptr,strlen(p[j].s)) && is_space(*(ptr+strlen(p[j].s)))) {
					p[j].c++;
					if (p[j].c>p[j].t) {
						p[j].t *= 2;
						p[j].i = realloc (p[j].i, p[j].t*sizeof(int));
					}
					p[j].i[p[j].c-1]=cnt;
					break;
				}
			}
			cnt++;
			ptr = strchr(ptr,' ');
			if (ptr==NULL) {
				break;
			}
			while (*ptr==' ') {
				ptr++;
			}
		}
	}
	fclose (fp);

	for (i=0;i<d;i++) {
		printf ("%s -> %d",p[i].s,p[i].c);
		if (p[i].c) {
			printf (", (");
			for (j=0;j<p[i].c;j++) {
				printf ("%d, ",p[i].i[j]);
			}
			printf ("\b\b)\n");
		}
		else {
			printf ("\n");
		}
		free (p[i].i);
	}
	free (p);
	return 0;
}

