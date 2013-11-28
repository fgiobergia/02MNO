#include "Queue.h"

Queue NewQueue () {
	Queue q;
	q = malloc(sizeof(*q));
	q->head = NULL;
	q->tail = q->head;
	return q;
}

void Put (Queue q, Item itm) {
	Node *n;
	if (q->head == NULL) {
		q->head = malloc(sizeof(*q->head));
		q->head->next = NULL;
		q->head->value = itm;
		q->tail = q->head;
	}
	else {
		n = malloc (sizeof(*n));
		n->value = itm;
		n->prev = NULL;
		n->next = q->tail;
		q->tail->prev = n;
		q->tail = n;
	}
}

Item Get (Queue q) {
	Item itm;
	itm = q->head->value;
	q->head = q->head->prev;
	q->head->next = NULL;
	return itm;
}

void PrintQueue (Queue q) {
	Node *n;
	for (n=q->tail;n!=NULL;n=n->next) {
		printf ("%08x\n",n->value);
	}
}

int SaveQueue (Queue q, char *filepath) {
	FILE *fp;
	Node *n;
	if ((fp = fopen (filepath, "w"))==NULL) {
		return 0;
	}
	for (n=q->head;n!=NULL;n=n->prev) {
		fprintf (fp,"%08x\n",n->value);
	}
	fclose (fp);
	return 1;
}

Queue LoadQueue (char *filepath) {
	FILE *fp;
	Queue q;
	Item itm;
	char line[128];
	q = NewQueue ();
	if ((fp=fopen(filepath,"r"))==NULL) {
		return NULL;
	}
	while (fgets(line,sizeof(line),fp)) {
		sscanf (line,"%x",&itm);
		Put (q,itm);
	}
	fclose (fp);
	return q;
}
	
