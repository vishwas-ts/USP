#include <unistd.h>
#include <errno.h>
#include <stdio.h>

ssize_t readblock(int fd, void *buf, size_t size) {
	char *bufp;
	size_t bytestoread;
	ssize_t bytesread;
	size_t totalbytes;

	for (bufp = buf, bytestoread = size, totalbytes = 0;
			bytestoread > 0;
			bytestoread -= bytesread, bufp +=bytesread) {
		if ((bytesread == 0) && (totalbytes == 0)) {
			return 0;
		}
		if (bytesread == 0) {
			errno = EINVAL;
			return -1;
		}
		if ((bytesread == -1) && (errno != EINTR))
			return -1;
		if (bytesread == -1)
			bytesread = 0;
		totalbytes += bytesread;
	}

	return totalbytes;
}


#ifdef DEBUG_READBLOCK

struct {
	int x;
	int y;
} point;


int main(int argc,  char *argv[]) {

	if (readblock(STDIN_FILENO, &point, sizeof(point)) <= 0)
	       fprintf(stderr, "Cannot read a point\n");

	return 0;
}	
#endif /* DEBUG_ROADBLCK */
