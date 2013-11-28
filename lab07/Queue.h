#include <stdio.h>
#include <stdlib.h>

typedef int Item;

typedef struct {
	Item value;
	void *next;
	void *prev;
} Node;

typedef struct {
	Node *head;
	Node *tail;
} *Queue;

Queue NewQueue ();
void Put (Queue, Item);
Item Get (Queue);
void PrintQueue (Queue);
int SaveQueue (Queue, char *);
Queue LoadQueue (char *);
