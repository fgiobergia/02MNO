#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define	__NO_ARGS__		0x00
#define	__INVALID_FILES__	0x01

void error (int errcode, char *arg) {
	switch (errcode) {
		case __NO_ARGS__:
			fprintf (stderr, "[!] Utilizzo: %s <file_compresso> <file_associazioni> <file_output>\n", arg);
			break;
		case __INVALID_FILES__:
			fprintf (stderr, "[!] Impossibile aprire i file forniti.\n");
			break;
		default:
			break;
	}
	exit (0);
}

char **load_keys (FILE *fp) {
	char **w,line[128];
	int i;
	w = calloc (100,sizeof(char*));
	while (fgets (line, sizeof(line), fp)) {
		sscanf (line, "%d %s",&i,line);
		w[i] = malloc ((strlen(line)+1)); // sizeof(char) == 1
		strcpy (w[i],line);
	}
	return w;
}

void gen_file (FILE *in, FILE *out, char **w) {
	char line[128];
	int i,n;
	while (fgets (line,sizeof(line),in)) {
		for (i=0;i<strlen(line);i++) {
			if (line[i]=='$') {
				if (sscanf (line+i+1,"%d",&n)) {
					fprintf (out, "%s", w[n]);
					do {
						i++;
					} while (*(line+i)>='0' && *(line+i)<='9');
					i--;
				}
				else {
					fprintf (out,"$");
				}
			}
			else {
				fprintf (out, "%c", line[i]);
			}
		}
	}

}

int main (int argc, char *argv[]) {
	FILE *fp,*keys,*out;
	char **w;
	int i;
	if (argc!=4) {
		error (__NO_ARGS__, argv[0]);
	}
	fp = fopen (argv[1],"r");
	keys = fopen (argv[2],"r");
	out = fopen (argv[3],"w");
	if (fp==NULL || keys==NULL || out==NULL) {
		error (__INVALID_FILES__,NULL);
	}
	w = load_keys (keys);
	gen_file (fp,out,w);
	
	for (i=0;i<100;i++) {
		/* free(w[i]) dovrebbe essere "sicuro" da fare
		 * anche se w[i] non contiene un puntatore:
		 * gli indirizzi non allocati vengono inizializzati
		 * a NULL usando calloc(); e free(NULL) non compie
		 * alcuna azione
		 * (diversi OS azzerano la memoria richiesta prima
		 * di fornirla per motivi di sicurezza. malloc non 
		 * lo fa a priori, mentre calloc si')
		 */
		 free (w[i]);
	}
	free(w);
	fclose(keys);
	fclose(fp);
	fclose(out);
	return 0;
}


