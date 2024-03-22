#include <stdio.h>
#include <stdlib.h>

#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>


int main(int argc, char *argv[]) {

	if (argc != 3) {
		fprintf(stderr, "Usage: %s sleeptime loopfactor\n", argv[0]);
		return 1;
	}

	int sleeptime = atoi(argv[1]);
	int loop_factor = atoi(argv[2]);

	for (int i = 0; i < loop_factor; i++) {
		sleep(sleeptime);
		fprintf(stderr, "%d. Process ID:%ld\n", i, (long)getpid());
	}

	return 0;
}
