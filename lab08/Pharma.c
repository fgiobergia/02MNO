#include "Pharma.h"

PharmaList PInit (int size) {
	PharmaList pl;
	int i;
	pl = malloc (sizeof(*pl));
	pl->list = malloc (size*sizeof(PharmaItem));
	pl->b = 0;
	return pl;
}

int PGetSize (PharmaList pl) {
	return pl->b;
}

int PAddPharma (PharmaList pl, int v[3]) {
	pl->list[pl->b].category = v[0];
	pl->list[pl->b].name = v[1];
	pl->list[pl->b++].company = v[2];
	return pl->b-1;
}

int PGetData (PharmaList pl, int p, int data) {
	switch (data) {
		case CATEGORY:
			return pl->list[p].category;
			break;
		case NAME:
			return pl->list[p].name;
			break;
		case COMPANY:
			return pl->list[p].company;
			break;
		default:
			return -1;
			break;
	}
}

void PRemoveLast (PharmaList pl) {
	pl->b--;
}

	
