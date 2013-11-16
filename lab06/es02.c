#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <linux/types.h>

#define	INPUT	"input.txt"

void new_column (__u8 v[], __u8 **s, int p, int n) {
	int i;
	if (p==n) {
		for (i=0;i<n;i++) {
			printf ("%c",(!v[i])?'X':v[i]+48);
		}
		printf ("\n");
		return ;
	}
	for (i=0;i<3;i++) {
		if (s[p][i]) {
			v[p]=i;
			new_column (v,s,p+1,n);
		}
	}
}

int main () {
	__u8 **s,*v;
	FILE *fp;
	char line[8];
	int i,j,k;
	fp = fopen (INPUT, "r");
	i = 0;
	j = 1;
	s = malloc (sizeof(__u8*));
	while (fgets (line,sizeof(line),fp)) {
		if (i<=j) {
			j *= 2;
			s = realloc (s,j*sizeof(__u8*));
		}
		s[i]=calloc(3,sizeof(__u8));
		for (k=0;k<strlen(line)-1;k++) {
			s[i][(line[k]=='X')?0:line[k]-48]=1;
		}
		i++;
	}
	v = malloc (i);
	new_column (v,s,0,i);
	fclose (fp);
	return 0;
}

