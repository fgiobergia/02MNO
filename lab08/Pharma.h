#include <stdio.h>
#include <stdlib.h>

#define	CATEGORY	0x00
#define	NAME		0x01
#define	COMPANY		0x02

typedef struct {
	int category;
	int name;
	int company;
} PharmaItem;

typedef struct {
	PharmaItem *list;
	int b;
} *PharmaList;

PharmaList PInit (int);
int PGetSize (PharmaList);
int PAddPharma (PharmaList, int *v);
int PGetData (PharmaList, int, int);
void PRemoveLast (PharmaList);
