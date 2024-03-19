#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int makeargv(const char *s, const char *delimiters, char ***argvp);


int main(int argc, char* argv[]) {
	char **myargv;
	char delim[] = " \t";
	pid_t childpid;

	if (argc != 2) {
		fprintf(stderr, "Usage: %s string\n", argv[0]);
		return 1;
	}

	childpid = fork();
	if (childpid == -1) {
		perror("Failed to fork");
		return 1;
	}
	
	if (childpid == 0) {
		if (setsid() == -1) 
			perror("Child failed to become a session leader");
		else if (makeargv(argv[1], delim, &myargv) == -1)
			fprintf(stderr, "Child failed to construct argument array\n");
		else {
			execvp(myargv[0], &myargv[0]);
			perror("Child failed to exec command");
		}
		return 1;
	}

	return 0;
}	


