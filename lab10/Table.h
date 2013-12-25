#include <stdlib.h>
#include <string.h>

typedef struct {
	char **list;
	int n;
} *Table;

Table NewTable (int, int);
int AddValue (Table, char*);
char *GetString (Table, int);
int GetId (Table, char *);
