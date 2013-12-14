#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define	LEFT	0
#define	RIGHT	1
#define	BINSER	2
#define	ITEM	3

typedef struct {
	char *str;
	int c;
} *Item;

typedef struct bst {
	Item itm;
	int children;
	struct bst *l;
	struct bst *r;
	struct bst *parent;
} *BST;

Item NewItem (char *, int);
BST BSTInit ();
BST BSTSearch (BST, Item);
void BSTEnter (BST, Item);
Item BSTNext (BST, Item);
Item BSTPrev (BST, Item);
void BSTDelete (BST, Item);
void BSTDisplay (BST);
