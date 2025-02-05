#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


int main(int argc, char *argv[]) {
	pid_t childpid;
	pid_t waitreturn;
	int i, n;


	if (argc != 2) {
		fprintf(stderr, "Usage: %s processes\n", argv[0]);
		return 1;
	}

	n = atoi(argv[1]);

	for (i = 1; i < n; i++) {
		if (childpid = fork())
			break;
	}

	while ((childpid != (waitreturn = wait(NULL))))
		if ((waitreturn == -1) && (errno != EINTR))
			break;

	fprintf(stderr, "I am process %ld, my parent is %ld\n",
			(long)getpid(), (long)getppid());

	return 0;
}
