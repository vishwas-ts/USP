#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "listlib.h"

int runproc(char *cmd) {
	data_t execute;
	
	if (time(&(execute.time)) == -1)
		return -1;

	execute.string = cmd;
	if (execute.string == NULL)
		return -1;


	if (system(cmd) == -1)
		return -1;

	return adddata(execute);
}

void showhistory(FILE *f) {
	data_t data;
	int key;

	key = accessdata();
	if (key == -1) {
		fprintf(f, "No history\n");
		return;
	}

	while (!getdata(key, &data) && (data.string != NULL)) {
		fprintf(f, "Command: %s\nTime: %s\n",data.string, ctime(&(data.time)));
		free(data.string);
	}
}
