#include <stdio.h>
#include <stdlib.h>

#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int r_wait(int* statloc);
int makeargv(const char *s, const char *delimiters, char ***myargv);

int main(int argc, char *argv[]) {
	char delim[] = " \t";
	char **myargv;

	if (argc != 2) {
		fprintf(stderr, "Usage: %s string", argv[0]);
		return 1;
	}

	pid_t childpid;

	childpid = fork();
	if (childpid == -1) {
		perror("Failed to fork");
		return 1;
	}

	if (childpid == 0) {
		if (makeargv(argv[1], delim, &myargv) == -1) {
			perror("Child failed to construct argument array");
		}
		else {
			execvp(myargv[0], &myargv[0]);
			perror("Failed to execute argv command");
		}
		return 1;
	}

	if (childpid != r_wait(NULL)) {
		perror("Parent failed to wait");
		return 1;
	}

	return 0;
}



