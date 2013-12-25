#include "Table.h"

Table NewTable (int size, int len) {
	Table t;
	int i;
	t = malloc (sizeof(*t));
	t->n = 0;
	t->list = malloc (size*sizeof(char*));
	return t;
}

int AddValue (Table t, char *val) {
	t->list[t->n] = strdup(val);
	t->n++;
	return t->n-1;
}

char *GetString (Table t, int id) {
	return t->list[id];
}

int GetId (Table t, char *str) {
	int i;
	for (i=0;i<t->n;i++) {
		if (!strcmp(str,t->list[i])) {
			return i;
		}
	}
	return -1;
}

