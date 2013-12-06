#include "Table.h"

Table TInit (int size, int len) {
	int i;
	Table t;
	t = malloc (sizeof(*t));
	t->v = malloc (size*sizeof(char*));
	for (i=0;i<size;i++) {
		t->v[i] = malloc (len*sizeof(char*));
	}
	t->b = 0;
	return t;
}

int TAddValue (Table t, char *value) {
	strcpy (t->v[t->b++], value);
	return t->b-1;
}

char *TGetValue (Table t, int id) {
	return t->v[id];
}

int TGetId (Table t, char *p) {
	int i;
	for (i=0;i<t->b;i++) {
		if (!strcmp(t->v[i],p)) {
			return i;
		}
	}
	return -1;
}

int TGetSize (Table t) {
	return t->b;
}

