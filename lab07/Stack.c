#include "Stack.h"

Stack NewStack (int size) {
	Stack stk;
	stk = malloc (sizeof(*stk));
	stk->max = size;
	stk->s = malloc (stk->max*sizeof(Item));
	stk->p = 0;
	return stk;
}

void Push (Stack stk, Item itm) {
	stk->s[stk->p++]=itm;
}

Item Pop (Stack stk) {
	return stk->s[--stk->p];
}

void PrintStack (Stack stk) {
	int i;
	for (i=0;i<stk->p;i++) {
		printf ("0x%08x: %08x\n",i,stk->s[i]);
	}
}

int SaveStack (Stack stk, char *filepath) {
	FILE *fp;
	int i;
	if ((fp = fopen (filepath,"w"))==NULL) {
		return 0;
	}
	fprintf (fp,"%d\n",stk->max);
	for (i=0;i<stk->p;i++) {
		fprintf (fp,"%08x\n",stk->s[i]);
	}
	fclose (fp);
	return 1;
}

Stack LoadStack (char *filepath) {
	Stack stk;
	FILE *fp;
	char line[128];
	int i;
	stk = malloc (sizeof(*stk));
	if ((fp=fopen(filepath,"r"))==NULL) {
		return 0;
	}
	fgets(line,sizeof(line),fp);
	sscanf(line,"%d",&(stk->max));
	stk->s = malloc(stk->max*sizeof(Item));
	i = 0;
	while (fgets(line,sizeof(line),fp)) {
		sscanf (line,"%x",&(stk->s[i++]));
	}
	fclose (fp);
	stk->p = i;
	return stk;
}

