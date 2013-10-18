#include <stdio.h>
#include <string.h>

#define	STOP	"stop"

int periodic (char *s) {
	int i,d;
	/* Se nella prima meta' della stringa non 
	 * c'e' una parola che si ripete, si puo'
	 * evitare di  controllare l'altra meta'.
	 */
	for (i=1;i<=strlen(s)/2;i++) {
		d = i;
		while (!strncmp(s,s+d,i) && d<strlen(s)) {
			d+=i;
		}
		if (d>=strlen(s)) {
			return i;
		}
	}
	return 0;
}

int main () {
	char line[32];
	int p;
	while (1) {
		printf ("< ");
		scanf ("%30s",line);

		/* Dato che il programma non deve fare controlli
		 * quando si inserisce la parola STOP, uso un 
		 * controllo nel ciclo,con annesso break in caso
		 * affermativo, per evitare di effettuare sia il
		 * controllo nel ciclo per non stampare l'output
		 * che nella condizione del ciclo while.
		 */
		if (!strcmp(line,STOP)) {
			break;
		}

		p = periodic (line);
		if (p) {
			printf ("Periodica di periodo %d\n",p);
		}
		else {
			printf ("Non periodica\n");
		}
	}
	return 0;
}

