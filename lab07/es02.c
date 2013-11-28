#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Stack.h"

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
	Stack s;
	char line[128],cmd,*arg;
	do {
		printf ("< ");
		fgets (line,sizeof(line),stdin);
		get_args (&cmd,&arg,line);
		switch (cmd) {
			case 'n':
				s = NewStack (atoi(arg));
				break;
			case 'l':
				s = LoadStack (arg);
				break;
			case 's':
				SaveStack (s,arg);
				break;
			case 'p':
				Push (s,atoi(arg));
				break;
			case 'd':
				PrintStack(s);
				break;
			case 'o':
				printf ("%d\n",Pop(s));
				break;
			case 'h':
				printf ("n <size>:\tNew stack\n"
				        "l <file>:\tLoad stack from file\n"
					"s <file>:\tSave stack to file\n"
					"p <val>:\tPush val in stack\n"
					"o:\t\tPop last stack value\n"
					"d:\t\tDisplay stack\n"
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

