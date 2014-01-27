#include <stdlib.h>
#include <string.h>

typedef struct {
	char **m;
	int n;
} *Table;

Table NewTable (int, int);
int TableNewValue (Table, char *);
char *TableGetValue (Table, int);
int TableGetId (Table, char *);
