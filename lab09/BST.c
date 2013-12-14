#include "BST.h"

Item NewItem (char *v, int code) {
	Item itm;
	itm = malloc(sizeof(*itm));
	itm->str = strdup (v);
	itm->c = code;
	return itm;
}

BST BSTInit () {
	BST b;
	b = malloc (sizeof(*b));
	b->itm = NULL;
	b->l = NULL;
	b->r = NULL;
	b->parent = NULL;
	b->children = 0;
}

BST BSTSearch (BST b, Item i) {
	if (b == NULL) {
		return NULL;
	}
	if (b->itm->c == i->c) {
		return b;
	}
	if (i->c<b->itm->c) {
		// left
		return BSTSearch(b->l,i);
	}
	else {
		//right;
		return BSTSearch(b->r,i);
	}
}

void BSTEnter (BST b, Item i) {
	BST a,p;
	char choice;
	if (b->itm == NULL) {
		b->itm = i;
		return ;
	}
	for (a=b;a!=NULL;) {
		p = a;
		a->children++;
		if (i->c<a->itm->c) {
			choice = LEFT;
			a = a->l;
		}
		else {
			choice = RIGHT;
			a = a->r;
		}
		// Si assume che non ci siano valori uguali nei codici
	}
	a = malloc (sizeof(*a));
	a->itm = i;
	a->parent = p;
	a->l = NULL;
	a->r = NULL;
	a->r = 0;
	if (choice==LEFT) {
		p->l = a;
	}
	else {
		p->r = a;
	}
}

void *BSTGetNext (BST b, void *i, int ivalue) {
	BST a;
	if (ivalue == ITEM) {
		a = BSTSearch(b,(Item)i);
	}
	else {
		a = (BST)i;
	}
	if (a==NULL) {
		return NULL;
	}
	if (a->r != NULL) {
		for (a=a->r;a->l!=NULL;a=a->l);
		return a->itm;
	}
	for (;a->parent->l!=a;a=a->parent);
	return a->parent->itm;
}

Item BSTNext (BST b, Item i) {
	return BSTGetNext(b,(void*)i,ITEM);
}

void *BSTGetPrev (BST b, void *i, int ivalue) {
	BST a;
	if (ivalue == ITEM) {
		a = BSTSearch(b,(Item)i);
	}
	else {
		a = (BST)i;
	}
	if (a==NULL) {
		return NULL;
	}
	if (a->l != NULL) {
		for (a=a->l;a->r!=NULL;a=a->r);
		return a->itm;
	}
	for (;a->parent->r!=a;a=a->parent);
	return a->parent->itm;
}

Item BSTPrev (BST b, Item i) {
	return BSTGetPrev (b,(void*)i,ITEM);
}

void BSTDelete (BST b, Item i) {
	BST a;
	Item c;
	a = BSTSearch(b,i);
	if (a->l == NULL && a->r == NULL) {
		if (a->parent->l==a) {
			a->parent->l = NULL;
		}
		else {
			a->parent->r = NULL;
		}
	}
	else if (a->l == NULL && a->r != NULL) {
		if (a->parent->l==a) {
			a->parent->l = a->r;
		}
		else {
			a->parent->r = a->r;
		}
		a->r->parent = a->parent;
		//a = a->r;

	}
	else if (a->l != NULL && a->r == NULL) {
		if (a->parent->l==a) {
			a->parent->l = a->l;
		}
		else {
			a->parent->r = a->l;
		}
		a->l->parent = a->parent;
		//a = a->l;
	}
	else {
		c = BSTGetNext (NULL,(void*)a,BINSER);
		BSTDelete (b, c);
		a->itm = c;
	}
}

void BSTDisplay (BST b) {
	if (b == NULL) {
		return ;
	}
	BSTDisplay (b->l);
	printf ("%d : %s\n",b->itm->c, b->itm->str);
	BSTDisplay (b->r);
}

