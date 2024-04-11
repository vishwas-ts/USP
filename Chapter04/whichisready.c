#include <unistd.h>
#include <errno.h>
#include <sys/select.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int whichisready(int fd1, int fd2) {
	int maxfd;
	int ndfs;
	fd_set readset;

	if ((fd1 < 0) || (fd1 >= FD_SETSIZE) ||
			(fd2 < 0) || (fd2 >= FD_SETSIZE)) {
		errno = EINVAL;
		return -1;
	}

	maxfd = (fd1 > fd2) ? fd1 : fd2;

	FD_ZERO(&readset);
	FD_SET(fd1, &readset);
	FD_SET(fd2, &readset);

	ndfs = select(maxfd + 1, &readset, NULL, NULL, NULL);
	if (ndfs == -1)
		return -1;

	if (FD_ISSET(fd1, &readset))
		return fd1;

	if (FD_ISSET(fd2, &readset))
		return fd2;

	errno = EINVAL;
	return -1;
}
