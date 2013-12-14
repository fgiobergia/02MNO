#include <stdlib.h>
#include <string.h>

typedef struct {
	int priority;
	char *taskname;
} *Job;

Job NewJob (char *, int);
void DismissJob (Job);
