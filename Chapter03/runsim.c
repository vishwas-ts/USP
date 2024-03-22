#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <limits.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>

int r_wait(int *chdrtn);

int makeargv(const char *s, const char *delimiters, char ***myargv);
void freemakeargv(char **argv);

int main(int argc, char *argv[]) {
	pid_t childpid;
	int pr_limit; 
	int pr_count = 0;
	char **myargv;
	char myarg[MAX_CANON];
	char delim[] = " \t";


	if (argc != 2) {
		fprintf(stderr, "Usage: %s processlimit\n", argv[0]);
		return 1;
	}

	pr_limit = atoi(argv[1]);


	while (1) {
		if (pr_count >= pr_limit) {
			if (r_wait(NULL) == -1)
				perror("Could not wait for child");

			pr_count--;
			continue;
			
		}


		if (fgets(myarg, MAX_CANON, stdin) == NULL) {
			while (pr_count != 0) {
				if (r_wait(NULL)  == -1) 
					perror("Failed to wait for children");
				pr_count--;
			}
			return 0;
		}

		if (*(myarg + strlen(myarg) - 1) == '\n')
		*(myarg + strlen(myarg) - 1) = '\0';

		if (makeargv(myarg, delim, &myargv) == -1) {
			fprintf(stderr, "Unable to create argument array\n");
			return 1;
		}

		if ((childpid = fork()) > 0) {

			pr_count++;
				
			if (waitpid(-1, NULL, WNOHANG) > 0)
				pr_count--;
			freemakeargv(myargv);
			
		}
		else {
			execvp(myargv[0], &myargv[0]);
			perror("Failed to execute child process");
			return 1;
		}

	}
	return 0;
}





