#include "Recipe.h"

Recipe NewRecipe (FILE *fp, Table in, Table rc) {
	Recipe r;
	char name[32],line[128];
	int i;

	r = malloc (sizeof(*r));
	fgets (line,sizeof(line),fp);
	sscanf (line, "%s %d %d",name,&r->price,&r->ingr_num);
	r->nameid = AddValue(rc,name);

	r->ingrs = malloc (r->ingr_num*sizeof(int*));
	for (i=0;i<r->ingr_num;i++) {
		r->ingrs[i] = malloc (2*sizeof(int)); // 0 ingr 1 quantity
		fgets (line,sizeof(line),fp);
		sscanf (line,"%s %d",name,&r->ingrs[i][1]);
		r->ingrs[i][0] = GetId(in,name);
	}

	return r;
}

int RecipeGetValue (Recipe r, int value) {
	switch (value) {
		case N_OF_INGREDIENTS:
			return r->ingr_num;
			break;
		case PRICE:
			return r->price;
			break;
		default:
			break;
	}
	return -1;
}

int *RecipeGetIngredients (Recipe r, int ingrn) {
	return r->ingrs[ingrn];
}
