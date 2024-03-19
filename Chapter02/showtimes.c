#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <limits.h>
#include <unistd.h>
#include <sys/times.h>

static void showtimes(void) {
	double ticks;
	struct tms tinfo;

	if ((ticks = (double) sysconf(_SC_CLK_TCK)) == -1)
		perror("Failed to determine clock ticks per second");
	else {
		fprintf(stderr, "User time:		%8.3f seconds\n",
				tinfo.tms_utime/ticks);
		fprintf(stderr, "System time:		%8.3f seconds\n",
				tinfo.tms_stime/ticks);
		fprintf(stderr, "Children's user time:	%8.3f seconds\n",
				tinfo.tms_cutime/ticks);
		fprintf(stderr, "Children's system time: %8.3f seconds\n",
				tinfo.tms_cstime/ticks);
	}
}

int main(int argc, char* arg[]) {
	if (atexit(showtimes)) {
		fprintf(stderr, "Failed to install exit handler\n");
		return 1;
	}

	return 0;
}
