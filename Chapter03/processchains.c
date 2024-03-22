#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>

int r_wait(int *strloc);

int main(int argc, char* argv[]) {
	int i, n;
	int j, nchars; 
	char mybuf[MAX_CANON];
	pid_t childpid;

	if (argc != 3) {
		fprintf(stderr, "Usage: %s processes nchars\n", argv[0]);
		return 1;
	}

	n = atoi(argv[1]);


	nchars = atoi(argv[2]);
	/*
	   m = atoi(argv[3]);
	   */

	for (i = 1; i < n; i++) {
		if ((childpid = fork()))
			break;
	}

	/* for (j = 0; j < k; j++) {
	   fprintf(stderr, "i:%d, process id:%ld, parent id:%ld, child id:%ld\n",
	   i, (long)getpid(), (long)getppid(), (long)childpid);
	   sleep(m);
	   } */
	if (r_wait(NULL) != childpid) {
		if (errno == ECHILD) 
			perror("No child present");
		else {	
			perror("Parent could not wait");
			return 1;
		}
	}

	for (j = 0; j < nchars; j++) {
		mybuf[j] = getchar();
	}
	mybuf[nchars] = '\0';
	fprintf(stderr, "Process ID:%ld Parent ID:%ld Buffer:%s\n", 
			(long)getpid(), (long)getppid(), mybuf);
	return 0;
}

