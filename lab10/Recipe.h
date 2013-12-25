#include <stdio.h>
#include <stdlib.h>
#include "Table.h"

#define	N_OF_INGREDIENTS	0
#define	PRICE			1

typedef struct {
	int nameid;
	int price;
	int ingr_num;
	int **ingrs;
} *Recipe;

Recipe NewRecipe (FILE *, Table, Table);
int RecipeGetValue (Recipe, int);
int *RecipeGetIngredients (Recipe, int);
