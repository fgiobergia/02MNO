#include "Job.h"
#include "PQ.h"

#define MAX(v,a,b,c)	(v[a]->priority>v[b]->priority&&v[a]->priority>v[c]->priority)?a:(v[b]->priority>v[a]->priority&&v[b]->priority>v[c]->priority)?b:c

PQ PQInit (int max) {
	PQ p;
	p = malloc (sizeof(*p));
	p->j_list = malloc (max*sizeof(Job));
	p->n = 0;
	return p;
}

void Heapify (PQ p, int i) {
	int max;
	Job j;
	if (i*2+1>=p->n) {
		return ;
	}
	max = MAX(p->j_list,i,2*i+1,2*i+2);
	if (max!=i) {
		j = p->j_list[i];
		p->j_list[i] = p->j_list[max];
		p->j_list[max] = j;
		Heapify (p,max);
	}
}

void PQInsert (PQ p, Job j) {
	int i,n;
	Job t;
	p->j_list[p->n] = j;
	for (i=p->n;i>=0;i=n) {
		n = (i-1)/2;
		if (p->j_list[n]->priority<p->j_list[i]->priority) {
			t = p->j_list[n];
			p->j_list[n] = p->j_list[i];
			p->j_list[i] = t;
		}
		else {
			break;
		}
	}
	p->n++;
}

Job PQExtractMax (PQ p) {
	Job r;
	if (!p->n) {
		return NULL;
	}
	r = p->j_list[0];
	p->j_list[0]=p->j_list[p->n-1];
	p->n--;
	Heapify (p,0);
	return r;
}
