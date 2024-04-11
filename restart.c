#include "restart.h"

#include <unistd.h>
#include <errno.h>

ssize_t r_read(int fd, void *buf, size_t size) {
	ssize_t retval;

	while (((retval = read(fd, buf, size)) == -1) && (errno == EINTR)) ;
	return retval;
}

ssize_t r_write(int fd, void *buf, size_t size) {
	char *bufp;
	size_t bytestowrite;
	ssize_t byteswritten;
	size_t totalbytes;

	for (bufp = buf, bytestowrite = size, totalbytes = 0;
			bytestowrite > 0;
			bufp += byteswritten, bytestowrite -= byteswritten) {
		byteswritten = write(fd, bufp, bytestowrite);
		if ((byteswritten == -1) && (errno != EINTR))
			return -1;

		if (byteswritten == -1)
			byteswritten = 0;
		totalbytes += byteswritten;
	}

	return totalbytes;
}

int r_close(int fd) {
	int retval;

	while (((retval = close(fd)) == -1) && (errno == EINTR)) 
		;

	return retval;
}
