#include <stdio.h>
#include "Table.h"
#include "Pharma.h"

void gen (PharmaList pl, PharmaList res, int k, int *v, int n, int max, Table t[3]) {
	int i,x[3];
	if (n==max) {
		for (i=0;i<PGetSize(res);i++) {
			printf ("%s (%s)\t",TGetValue(t[1],PGetData(res,i,NAME)),TGetValue(t[2],PGetData(res,i,COMPANY)));
		}
		printf ("\n");
		return ;
	}

	for (i=0;i<PGetSize(pl);i++) {
		if (PGetData(pl,i,CATEGORY)==n && v[PGetData(pl,i,COMPANY)]<k) {
			v[PGetData(pl,i,COMPANY)]++;
			x[0]=n;
			x[1]=PGetData(pl,i,NAME);
			x[2]=PGetData(pl,i,COMPANY);
			PAddPharma (res,x);

			gen (pl, res, k, v, n+1,max,t);

			PRemoveLast (res);
			v[PGetData(pl,i,COMPANY)]--;
		}
	}
}

void usage (char *name) {
	fprintf (stderr,"[!] Usage: %s <K>\n",name);
	exit (0);
}

int main (int argc, char *argv[]) {
	int k;
	Table tbs[3];
	PharmaList pl,res;
	FILE *fp;
	char line[128],name[32],*ptr;
	int n,d,id[3],v[10]={0};

	if (argc<2) {
		usage (argv[0]);
	}

	k = atoi(argv[1]);
	fp = fopen ("input.txt","r");
	tbs[0] = TInit (20,32);
	tbs[1] = TInit (50,32);
	tbs[2] = TInit (10,32);
	pl = PInit (50);
	res = PInit (50);
	
	while (fgets(line,sizeof(line),fp)) {
		ptr = line;
		for (d=0;d<3;d++) {
			sscanf (ptr,"%s%n",name,&n);
			ptr+=n;
			id[d] = TGetId(tbs[d],name);
			if (id[d]<0) {
				id[d] = TAddValue(tbs[d],name);
			}
		}
		PAddPharma (pl, id);
	}
	
	gen(pl,res,k,v,0,TGetSize(tbs[0]),tbs);
	
	fclose (fp);
	return 0;
}

