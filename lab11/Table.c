#include "Table.h"

Table NewTable (int n, int l) {
	Table t;
	t = malloc(sizeof(*t));
	t->list = malloc(n*sizeof(char*));
	t->n = 0;
	return t;
}

int TableAddValue (Table t, char *value) {
	t->list[t->n] = strdup (value);
	t->n++;
	return t->n-1;
}

char *TableGetString (Table t, int id) {
	return t->list[id];
}

int TableGetId (Table t, char *str) {
	int i;
	for (i=0;i<t->n;i++) {
		if (!strcmp(str,t->list[i])) {
			return i;
		}
	}
	return -1;
}

