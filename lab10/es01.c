#include <stdio.h>
#include "Recipe.h"

#define	IN1	"in1.txt"
#define	IN2	"in2.txt"

int max,*maxv;

int *memdup (int *v, int n) {
	int *m,i;
	m = malloc (n*sizeof(int));
	for (i=0;i<n;i++) {
		m[i]=v[i];
	}
	return m;
}

int get_amount (int **ingrs, int ingr, int n) {
	return ingrs[ingr][1];
}

void update_amount (int **ingrs, int ingr, int change, int n) {
	ingrs[ingr][1] += change;
}

int can_use (Recipe r, int **ingrs, int ingrn) {
	int i,d,*in;
	for (i=0;i<RecipeGetValue(r,N_OF_INGREDIENTS);i++) {
		in = RecipeGetIngredients(r,i);
		if (get_amount(ingrs,in[0],ingrn)<in[1]) {
			return 0;
		}
	}
	return 1;
}

void find_best (Recipe *r, int n, int tot, int **ingrs, int ingrn, int *v) {
	int i,j,*in,c,stop,**bck;
	bck = malloc(ingrn*sizeof(int));
	for(j=0;j<ingrn;j++) {
		bck[j]=malloc(2*sizeof(int));
		bck[j][0]=ingrs[j][0];
		bck[j][1]=ingrs[j][1];
	}
	for (i=0,c=0;i<n;i++) {
		for (j=0,stop=0;j<RecipeGetValue(r[i],N_OF_INGREDIENTS);j++) {
			in = (int*)RecipeGetIngredients(r[i],j);
			if (get_amount(ingrs,in[0],ingrn)<in[1]) {
				break;
			}
			update_amount(ingrs,in[0],-in[1],ingrn);
		}
		if (j==RecipeGetValue(r[i],N_OF_INGREDIENTS)) {
			c = 1;
			v[i]++;
			find_best (r,n,tot+RecipeGetValue(r[i],PRICE),ingrs,ingrn,v);
			v[i]--;
		}
		/* This shouldn't work,
		 * but it does, and it's way
		 * more efficient (time-wise)
		 * compared to the previous version.
		 *
		 * Let's keep it this way.
		 */
		ingrs=bck;
	}
	if (!c) {
		if (tot>max) {
			max = tot;
			maxv = memdup(v,ingrn);
		}
		return ;
	}	
}

int main () {
	FILE *fp;
	char line[128],name[32];
	Table in,rc;
	Recipe *r;
	int **ingr,size_i,size_r,i,*v;

	fp = fopen (IN1, "r");
	fgets (line,sizeof(line),fp);
	size_i = atoi(line);
	in = NewTable(size_i,32);
	ingr = malloc (size_i*sizeof(int*));
	
	i = 0;
	while (fgets(line,sizeof(line),fp)) {
		ingr[i] = malloc (2*sizeof(int)); // 0 name, 1 amount
		sscanf (line,"%s %d",name,&ingr[i][1]);
		ingr[i][0] = AddValue (in, name);
		i++;
	}
	fclose (fp);
	
	fp = fopen (IN2, "r");
	fgets (line,sizeof(line),fp);
	size_r = atoi(line);
	rc = NewTable(size_r,32);
	r = malloc (size_r*sizeof(Recipe));

	for (i=0;i<size_r;i++) {
		r[i] = NewRecipe (fp,in,rc);
	}
	v = calloc (size_r,sizeof(int));
	find_best (r,size_r,0,ingr,size_i,v);
	printf ("max: %d\n",max);
	for (i=0;i<size_r;i++) {
		if (maxv[i]) {
			printf ("%d x %s\n",maxv[i],GetString(rc,i));
		}
	}
	return 0;
}

