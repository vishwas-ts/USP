#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <unistd.h>
#include <errno.h>


void freemakeargv(char **argv) {
	if (argv == NULL)
		return;
	if (*argv != NULL)
		free(*argv);
	free(argv);
}

int make_argv_delim(const char *s, const char *delimiters, char ***argvp) {
	int error;
	int i;
	int numtokens;
	const char* snew;
	char *t;

	if ((s == NULL) || (delimiters == NULL) || (argvp == NULL)) {
		errno = EINVAL;
		return -1;
	}

	*argvp = NULL;
	snew = s + strspn(s, delimiters);
	printf("The new string after stripping intial delimiters is: %s\n", snew);

	if ((t = malloc(strlen(snew) + 1)) == NULL)
		return -1;

	strcpy(t, snew);

	numtokens = 0;
	if (strtok(t, delimiters) != NULL)
		for (numtokens = 1; strtok(NULL, delimiters) != NULL; numtokens++);
	printf("The number of tokens is: %d\n", numtokens);

	if ((*argvp = malloc((numtokens + 1) * sizeof(char *))) == NULL) {
		error = errno;
		free(t);
		errno = error;
		return -1;
	}

	if (numtokens == 0)
		free(t);
	else {
		strcpy(t, snew);
		**argvp = strtok(t, delimiters);
		for (i = 1; i < numtokens; i++)
			*((*argvp) + i) = strtok(NULL, delimiters);
	}

	*((*argvp) + numtokens) = NULL;
	return numtokens;
}



int main(int argc, char **argv) {
	int i;
	char **myargv;
	char delim[] = " ";
	int num_tokens;

	char mytest[] = "This is a test";

	if ((num_tokens = make_argv_delim(mytest, delim, &myargv)) == -1)
		fprintf(stderr, "Failed to construct argument array with given deliminator\n");
	else 
		for (i = 0; i < num_tokens; i++)
			printf("%d: %s\n", i, myargv[i]);

	freemakeargv(myargv);
	return 0;
}
