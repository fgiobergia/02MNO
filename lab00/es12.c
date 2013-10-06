/* si assume che le tratte siano indicate senza ripetizioni */

#include <stdio.h>
#include <string.h>

#define	IN	"input.txt"

void reverse (char x[8], char *str) {
	strncpy (x,str+4,3);
	x[3]=32;
	strncat (x,str,3);
	x[7]=0;
}

int main () {
	FILE *fp;
	char t[200][10];
	char match[8]={0};
	int i,d,c;
	fp = fopen (IN, "r");
	i=0;
	c=0;
	while (fgets (t[i],sizeof(t[i]),fp)) {
		reverse (match,t[i]);
		for (d=0;d<i;d++) {
			if (!strncmp(match,t[d],7)) {
				printf ("%s\n",match);
				c++;
				break;
			}
		}
		memset (match,0,sizeof(match));
		i++;
	}
	printf ("%d\n",c);
	return 0;
}

