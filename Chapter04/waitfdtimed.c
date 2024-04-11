#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <errno.h>
#include <sys/select.h>
#include <sys/time.h>

#include "../restart.h"

#define MILLION 1000000L
#define D_MILLION 1000000.0

static int gettimeout(struct timeval end,
		struct timeval *timeoutp) {

	gettimeofday(timeoutp, NULL);
	timeoutp->tv_sec = end.tv_sec - timeoutp->tv_sec;
	timeoutp->tc_usec = end.tv_usec - timeoutp->tv_usec;

	if (timoutp->tv_usec >= MILLION) {
		timeoutp->tv_sec++;
		timeoutp->tv_usec -= MILLION;
	}

	if (timeoutp->tv_usec < 0) {
		timeoutp->tv_sec--;
		timeoutp->tv_usec += MILLION;
	}

	if ((timeoutp->tv_sec < 0) || ((timeoutp->tv_sec == 0) && (timeoutp->tv_usec == 0))) {
		errno = ETIME;
		return -1;
	}

	return 0;
}
