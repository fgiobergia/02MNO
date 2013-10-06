#include <stdio.h>
#include <string.h>

#define	IN	"input.txt"
#define	OUT	"output.txt"

int main () {
	FILE *in = fopen (IN,"r");
	FILE *out = fopen (OUT,"w");
	char line[1024],new[1024];
	int i,d,bl,k,j;
	while (fgets (line,sizeof(line),in)) {
		for (i=0,d=0,bl=0,k=1;i<strlen(line);i++) {
			if (line[i]!=32 || k) {
				new[d++]=line[i];
				k = (line[i]!=32);
			}
			else {
				bl++;
			}
		}
		new[d]=0;
		for (j=0;j<bl/2;j++) {
			fprintf (out, " ");
		}
		fprintf (out,"%s",new);
	}
	fclose(in);
	fclose(out);
	return 0;
}

