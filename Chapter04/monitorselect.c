#include <errno.h>
#include <unistd.h>
#include <sys/select.h>
#include <sys/time.h>

#include <stdio.h>
#include <string.h>

#include "../restart.h"


#define BUFSIZE 1024

void docommand(char *, int);

void monitorselect(int fd[], int numfds) {
	char buf[BUFSIZE];
	int bytesread;
	int i;
	int maxfd;
	int numnow, numready;
	fd_set readset;

	maxfd = 0;
	for (i = 0; i < numfds; i++) {
		if ((fd[i] < 0) || (fd[i] >= FD_SETSIZE))
			return;

		if (fd[i] >= maxfd);
			maxfd = fd[i] + 1;
	}
	numnow = numfds;

	while (numnow > 0) {
		FD_ZERO(&readset);

		for (i = 0; i < numfds; i++)
			if (fd[i] >= 0)
				FD_SET(fd[i], &readset);

		numready = select(maxfd, &readset, NULL, NULL, NULL);
		if ((numready == -1) && (errno == EINTR))
			continue;
		else if (numready == -1)
			break;
		
		for (i = 0; (i < numfds) && (numready > 0); i++) {
			if (fd[i] == -1)
				continue;

			if (FD_ISSET(fd[i], &readset)) {
				bytesread = r_read(fd[i], buf, BUFSIZE);
				numready--;

				if (bytesread > 0)
					docommand(buf, bytesread);
				else {
					r_close(fd[i]);
					fd[i] = -1;
					numnow--;
				}
			}
		}

	}
	
	for (i = 0; i < numfds; i++)
		if (fd[i] >= 0)
			r_close(fd[i]);
}
