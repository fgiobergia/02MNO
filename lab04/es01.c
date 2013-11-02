#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define	IN1	"input1.txt"
#define	IN2	"input2.txt"

struct word {
	char *s;
	int c;
};

int is_space (char ch) {
	return (ch==' ' || ch=='\n' || ch=='\t');
}

int main () {
	FILE *fp;
	struct word *p;
	int i,d,j;
	char line[128],*ptr;

	fp = fopen (IN1,"r");
	fgets (line,sizeof(line),fp);
	sscanf (line,"%d",&d);
	p = malloc (d*sizeof(struct word));
	for (i=0;i<d;i++) {
		fgets (line,sizeof(line),fp);
		line[strlen(line)-1]=0;
		p[i].s = strdup (line);
		p[i].c = 0;
	}
	fclose (fp);
	
	fp = fopen (IN2,"r");
	while (fgets (line, sizeof(line), fp)) {
		for (ptr=line;;) {
			for (j=0;j<d;j++) {
				if (!strncasecmp(p[j].s,ptr,strlen(p[j].s)) && is_space(*(ptr+strlen(p[j].s)))) {
					p[j].c++;
					break;
				}
			}
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
		printf ("%s -> %d\n",p[i].s,p[i].c);
	}
	free (p);
	return 0;
}

