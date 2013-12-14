#include <stdio.h>
#include <stdlib.h>
#include <linux/types.h>
#include "Job.h"
#include "PQ.h"

#define	N 3

void run_process (__u8 *m, Job j, PQ p) {
	int i;
	for (i=0;i<N;i++) {
		if (!m[i]) {
			if (j==NULL) {
				j = (Job)ExtractMax(p);
				if (j != NULL) {
					printf ("[+] Estratto %s (priorita' %d)\n",j->taskname,j->priority);
				}
			}
			if (j != NULL) {
				printf ("[+] Job %s in esecuzione sulla macchina %d\n",j->taskname,i+1);
				m[i]=1;
			}
			return ;
		}
	}
	PQInsert (p, j);
	printf ("[!] Job %s in attesa con priorita' %d\n",j->taskname,j->priority);
}

void get_done (PQ p, __u8 *m) {
	int i;
	for (i=0;i<N;i++) {
		if (m[i]) {
			m[i]=0;
			printf ("[+] Job sulla macchina %d terminato\n",i+1);
			run_process (m,NULL,p);
		}
	}
}

int main () {
	PQ p;
	Job a;
	int pr;
	char cmd[256],tname[256];
	__u8 busy[N] = {0};
	p = (PQ) PQInit (100);
	while (1) {
		printf ("< ");
		fgets (cmd,sizeof(cmd),stdin);
		switch (cmd[0]) {
			// n <priority> <task name> : New job called 'task name', with priority 'priority'
			case 'n':
				sscanf (cmd+1,"%d %s",&pr,tname);
				a = NewJob (tname,pr);
				run_process (busy,a,p);
				break;
			// r : Get jobs done and start new ones
			case 'r':
				get_done (p,busy);
				break;
			case 'q':
			// q : quit
				return 0;
				break;
			default:
				break;
		}
	}
	return 0;
}
