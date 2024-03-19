#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>

int main(int argc, char* argv[]) {
	pid_t childpid;
	int i, n;

	if (argc != 2) {
		fprintf(stderr, "Usage: %s processes\n", argv[0]);
		return 1;
	}

	n = atoi(argv[1]);

	for(i = 0; i < n; i++)
		if ((childpid = fork()) <= 0)
			break;

	fprintf(stderr, "i:%d process ID:%ld, parent ID:%ld, childID:%ld\n", 
			i, (long)getpid(), (long)getppid(), (long)childpid);

	return 0;
}


