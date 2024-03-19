#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <limits.h>

#include "log.h"

int runproc(char *cmd) {
	data_t execute;

	time(&execute.time);
	execute.string = cmd;

	if (system(cmd) == -1)
		return -1;

	return addmsg(execute);
}


int main(int argc, char *argv[]) {
	char cmd[MAX_CANON];
	char *file_str;

	while (fgets(cmd, MAX_CANON, stdin) != NULL) {
		if (*(cmd + strlen(cmd) - 1) == '\n')
			*(cmd + strlen(cmd) - 1) = '\0';
		if (strcmp(cmd, "history") == 0) {
			char *logstr = getlog();
			printf("%s", logstr);
		}
		else if (strncmp(cmd, "savelog", strlen("savelog")) == 0) {
			strtok(cmd, " ");
			file_str = strtok(NULL, " ");
			savelog(file_str);
		} 
		else if (strcmp(cmd, "clearlog") == 0) {
			clearlog();
		}
		else {
			if (runproc(cmd) == -1)
				perror("Unable to run command");
		}
	}

	return 0;
}
