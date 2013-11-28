#include <stdio.h>
#include <stdlib.h>

typedef int Item;

typedef struct {
	Item *s;
	int p;
	int max;
} *Stack;
Stack NewStack (int);
void Push (Stack, Item);
Item Pop (Stack);
void PrintStack (Stack);
int SaveStack (Stack, char *);
Stack LoadStack (char *);
