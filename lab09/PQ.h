#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int n;
	Job *j_list;
} *PQ;

PQ InitPQ (int);
void PQInsert (PQ , Job);
Job PQExtractMax (PQ);
