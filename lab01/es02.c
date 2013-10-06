#include <stdio.h>
#include <string.h>

int main () {
	FILE *fp;
	char fname[32],line[512];
	float x,y,z,tx,ty,tz;
	int i;
	printf ("< ");
	fgets (fname,sizeof(fname),stdin);
	fname[strlen(fname)-1]=0;
	fp = fopen (fname,"r");
	i=x=y=z=0;
	while (fgets (line,sizeof(line),fp)) {
		sscanf (line,"%f %f %f",&tx,&ty,&tz);
		x+=tx;
		y+=ty;
		z+=tz;
		i++;
	}
	printf ("Baricentro: %.1f %.1f %.1f\n",x/i,y/i,z/i);
	fclose(fp);
	return 0;
}
