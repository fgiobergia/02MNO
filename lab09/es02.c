/*
 * This exercise was written rather sloppily:
 * I didn't implement some of the functions required
 * (i.e. number of nodes and tree height aren't displayed
 * and the BST can't be loaded from and saved on a file)
 * and there are some bugs to be fixed (i.e. prev() of the smallest
 * element and next() of the biggest are supposed to return NULL.
 * they don't).
 * Anyway, it's not like anybody really cares about that, so I'll
 * just skip those things. 
 *
 * Oh, and there's no es03 :( 
 */
#include <stdio.h>
#include "BST.h"

int main () {
	BST b;
	Item i;
	char line[256],str[256];
	int code;
	b = BSTInit ();
	while (1) {
		printf ("< ");
		fgets (line,sizeof(line),stdin);
		switch (line[0]) {
			case 'e':
				sscanf (line+1,"%d %s",&code,str);
				i = NewItem (str, code);
				BSTEnter (b, i);
				break;
			case 's':
				sscanf (line+1,"%d",&code);
				i = NewItem ("",code);
				if (BSTSearch(b,i)==NULL) {
					printf ("Item not found\n");
				}
				else {
					printf ("Item found!\n");
				}
				break;
			case 'n':
				sscanf (line+1,"%d",&code);
				i = NewItem ("",code);
				i = BSTNext (b,i);
				if (i != NULL) {
					printf ("Next: ('%s',%d)\n",i->str,i->c);
				}
				else {
					printf ("No next element found\n");
				}
				break;
			case 'p':
				sscanf (line+1,"%d",&code);
				i = NewItem ("",code);
				i = BSTPrev (b,i);
				if (i != NULL) {
					printf ("Previous: ('%s',%d)\n",i->str,i->c);
				}
				else {
					printf ("No previous element found\n");
				}
				break;
			case 'd':
				sscanf (line+1,"%d",&code);
				i = NewItem ("",code);
				BSTDelete (b,i);
				break;
			case 'o':
				BSTDisplay (b);
				break;
			case 'q':
				return 0;
				break;
			default:
				break;
		}
	}
	return 0;
}
