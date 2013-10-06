#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define	IN1	"input.txt"
#define	IN2	"input2.txt"
#define	OUT	"output.txt"

struct std {
	char name[20];
	char surname[20];
	char mat[6];
	int w;
	int o;
} std;

float avg (int n1, int n2) {
	return (n1+n2)/2.0;
}

char *itoa (float f) {
	char *n;
	n=malloc(3);
	n[0]=48+((int)f/10);
	n[1]=48+((int)f%10);
	n[2]=0;
	return n;
}

int main () {
	struct std st[100];
	int i,d;
	float t;
	FILE *in,*out;
	char line[64];
	in = fopen (IN1, "r");
	i=0;
	while (fgets (line, sizeof(line), in)) {
		sscanf (line, "%s %s %s",st[i].surname,st[i].name,st[i].mat);
		st[i].w=0;
		st[i].o=0;
		i++;
	}
	fclose(in);
	in=fopen(IN2, "r");
	while (fgets (line, sizeof(line), in)) {
		for (d=0;d<i;d++) {
			if (!strncmp(st[d].mat,line,strlen(st[d].mat))) {
				sscanf (line+strlen(st[d].mat)+1, "%d %d",&st[d].w,&st[d].o);
			}
		}
	}
	fclose (in);
	out = fopen (OUT,"w");
	for(d=0;d<i;d++) {
		t = avg(st[d].w,st[d].o);
		fprintf (out, "%s %s %s %s\n",st[d].mat,st[d].surname,st[d].name,(!t)?"N.P.":(t==30)?"30L":(t<18)?"INSUF.":itoa(t));
	}
	fclose(out);
	return 0;
}

