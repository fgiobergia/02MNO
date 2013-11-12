#include <stdio.h>
#include <stdlib.h>

char *date2string (int ts) {
	char *str = malloc (11);
	int d,m,y;
	y = ts/(30*12);
	ts %=(30*12);
	m = ts/30;
	ts %=30;
	d = ts;
	sprintf (str, "%02d/%02d/%04d",d,m,y);
	return str;
}

int string2date (char *date) {
	int d,m,y,ret;
	sscanf (date, "%d/%d/%d",&d,&m,&y);
	ret = d+m*30+y*30*12;
	return ret;
}

void get_min_max (char *file, unsigned int *min, unsigned int *max) {
	FILE *fp;
	char line[1024];
	unsigned int mn,mx,date[3],tmp;
	mn=~0;
	mx=0;
	fp = fopen (file,"r");
	while (fgets (line, sizeof(line), fp)) {
		sscanf (line, "%d/%d/%d",&date[0],&date[1],&date[2]);
		tmp = string2date(line);
		if (tmp>mx) {
			mx=tmp;
		}
		if (tmp<mn) {
			mn=tmp;
		}
	}
	*min = mn;
	*max = mx;
	fclose (fp);
}

int main () {
	unsigned int min, max;
	get_min_max ("input.txt",&min,&max);
	printf ("min:  %s\n",date2string(min));
	printf ("max:  %s\n",date2string(max));
	printf ("diff: %s\n",date2string(max-min));
	return 0;
}

