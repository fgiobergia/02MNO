#include <stdio.h>

#define IN "input.txt"

int main () {
	FILE *fp;
	int x[2],y1[2],y2[2];
	float area;
	char line[512];
	fp = fopen (IN, "r");
	fgets (line,sizeof(line),fp);
	sscanf (line, "%d %d %d", &x[0],&y1[0],&y2[0]);
	area = 0;
	while (fgets(line,sizeof(line),fp)) {
		sscanf (line, "%d %d %d",&x[1],&y1[1],&y2[1]);
		area += ((x[1]-x[0])/2.0)*(y2[0]+y2[1]-y1[0]-y1[1]);
		x[0]=x[1];
		y1[0]=y1[1];
		y2[0]=y2[1];
	}
	printf ("%f\n", area);
	fclose (fp);
	return 0;
}

