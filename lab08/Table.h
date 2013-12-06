#include <stdlib.h>
#include <string.h>

typedef struct {
	int b;
	char **v;
} *Table;

Table TInit (int, int);
int TAddValue (Table, char *);
char *TGetValue (Table, int);
int TGetId (Table, char *);
int TGetSize (Table);
