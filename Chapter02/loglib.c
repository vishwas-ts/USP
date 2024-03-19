#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include <limits.h>
#include "log.h"

#ifndef MAX_CANON
#define MAX_CANON 8192
#endif /* MAX_CANON */
typedef struct list_struct {
	data_t data;
	struct list_struct *next;
} log_t;

static log_t *headptr = NULL;
static log_t *tailptr = NULL;

int addmsg(data_t data) {
	log_t *newlink = NULL;

	newlink = (log_t *)(malloc(sizeof(log_t) + strlen(data.string) + 1));
	if (newlink == NULL) {
		fprintf(stderr, "Unable to allocate memory for the new link\n");
		return -1;
	}

	newlink->data.time = data.time;
	newlink->data.string = (char *)(newlink + sizeof(log_t));
	strcpy(newlink->data.string, data.string);

	newlink->next = NULL;

	if (headptr == NULL) {
		headptr = newlink;
	}

	if (tailptr != NULL) {
		tailptr->next = newlink;
	}

	tailptr = newlink;
	return 0;
}


void clearlog(void) {
	log_t *currentlink = headptr;

	while (headptr != NULL) {
		currentlink = headptr;
		headptr = headptr->next;

		free(currentlink);
		currentlink = NULL;
	}

	tailptr = NULL;
}	

char * getlog(void) {
	size_t logstrsize = 1024;
	size_t currentlogsize = 0;

	char currentlog[1024];
	char timestr[26];

	if (headptr == NULL) {
		return NULL;
	}

	char *logstr = malloc(sizeof(char) * logstrsize);

	log_t *currentptr = headptr;
	while (currentptr != NULL) {
		if (ctime_r(&(currentptr->data.time), timestr) == NULL)
			return NULL;
		sprintf(currentlog, "%s %s\n", timestr, currentptr->data.string);
	       	if ((currentlogsize + strlen(currentlog) + 1) > logstrsize) {
			logstr = realloc(logstr, 2 * logstrsize);
			if (logstr == NULL) {
				fprintf(stderr, "Unable to reallocate string logstring to size: %ld\n", 2 * logstrsize);
				return NULL;
			}
			logstrsize *= 2;
		}
		
		strcpy(&logstr[currentlogsize], currentlog);	
		currentlogsize += strlen(currentlog);

		currentptr = currentptr->next;
	}

	return logstr;
}

int savelog(char *filename) {
	FILE *f = fopen(filename, "a");
	if (f == NULL) 
		return -1;

	char * logstr = getlog();

	size_t writesize = strlen(logstr);
	if (fwrite(logstr, writesize, sizeof(char), f) != writesize) {
		fprintf(stderr, "Unable to write to file\n");
		return -1;
	}
	fclose(f);

	return 0;
}
