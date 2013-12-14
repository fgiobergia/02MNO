#include "Job.h"

Job NewJob (char *name, int p) {
	Job j;
	j = malloc (sizeof(*j));
	j->priority = p;
	j->taskname = strdup(name);
	return j;
}

void DismissJob (Job j) {
	free (j);
}
