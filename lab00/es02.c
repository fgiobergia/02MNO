#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *strrev (char *str) {
	char *t;
	int i;
	t = malloc (strlen(str)+1);
	for (i=0;i<strlen(str);i++) {
		t[strlen(str)-i-1]=str[i];
	}
	t[strlen(str)]=0;
	return t;
}

char *sum (char *s1, char *s2, int base) {
	int i,a,b,rst,x,y;
	char *res,*ax;
	res = malloc (1);
	for (a=strlen(s1)-1,b=strlen(s2)-1,i=0,rst=0;(a>-1 || b>-1 || rst);a--,b--) {
		res = realloc (res,++i);
		x=(a>-1)?s1[a]-48:0;
		y=(b>-1)?s2[b]-48:0;
		res[i-1]=48+(x+y+rst)%base;
		rst=(x+y+rst)/base;
	}
	res = realloc (res,++i);
	res[i-1]=0;
	ax = strrev(res);
	free (res);
	return ax;

}

int main () {
	char s1[1024],s2[1024],*s;
	int base;
	do {
		printf ("< ");
		scanf ("%d",&base);
	} while (base<2 || base>10);
	printf ("< ");
	scanf ("%s",s1);
	printf ("< ");
	scanf ("%s",s2);
	s = sum (s1,s2,base);
	printf("> %s\n",s);
	free (s);
	return 0;
}
