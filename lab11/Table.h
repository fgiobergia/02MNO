#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	char **list;
	int n;
} *Table;

Table NewTable (int, int);
int TableAddValue (Table, char *);
char *TableGetString (Table, int);
int TableGetId (Table, char *);

