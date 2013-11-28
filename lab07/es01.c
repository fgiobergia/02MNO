#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Queue.h"

void get_args (char *ch, char **arg, char *p) {
	while (*p==' ') {
		p++;
	}
	*ch = *p++;
	while (*p==' ') {
		p++;
	}
	*arg = strndup (p,strlen(p)-1);
}

int main () {
	Queue q;
	char line[128],cmd,*arg;
	do {
		printf ("< ");
		fgets (line,sizeof(line),stdin);
		get_args (&cmd,&arg,line);
		switch (cmd) {
			case 'n':
				q = NewQueue ();
				break;
			case 'l':
				q = LoadQueue (arg);
				break;
			case 's':
				SaveQueue (q,arg);
				break;
			case 'p':
				Put (q,atoi(arg));
				break;
			case 'd':
				PrintQueue(q);
				break;
			case 'g':
				printf ("%d\n",Get(q));
				break;
			case 'h':
				printf ("n:\t\tNew queue\n"
				        "l <file>:\tLoad queue from file\n"
					"s <file>:\tSave queue to file\n"
					"p <val>:\tPut val in queue\n"
					"g:\t\tGet first queue value\n"
					"d:\t\tDisplay queue\n"
					"h:\t\tShow this message\n"
					"q:\t\tQuit\n");
				break;
			case 'q':
				break;
			default:
				printf ("No such command. Type 'h' for help\n");
				break;
		}		
	} while (cmd!='q');
	return 0;
}

