#include "Table.h"

Table NewTable (int m, int l) {
	int i;
	Table t;
	t = malloc (sizeof(*t));
	t->n = 0;
	t->m = malloc (m*sizeof(char*));
	return t;
}

int TableNewValue (Table t, char *v) {
	t->m[t->n++] = strdup (v);
	return t->n-1;
}

char *TableGetValue (Table t, int n) {
	return t->m[n];
}

int TableGetId (Table t, char *v) {
	int i;
	for (i=0;i<t->n;i++) {
		if (!strcmp(t->m[i],v)) {
			return i;
		}
	}
	return -1;
}
