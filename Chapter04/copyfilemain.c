#include <stdio.h>

#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>

#include "../restart.h"

#define READ_FLAGS O_RDONLY
#define WRITE_FLAGS (O_WRONLY | O_CREAT | O_EXCL)
#define WRITE_PERMS (S_IRUSR | S_IWUSR)

extern int copyfile(int fromfd, int tofd);

int main(int argc, char *argv[]) {
	int bytes;
	int fromfd, tofd;

	if (argc != 3) {
		fprintf(stderr, "Usage: %s from_file to_file\n", argv[0]);
		return 1;
	}

	if ((fromfd = open(argv[1], READ_FLAGS)) == -1) {
		perror("Failed to open input file");
		return 1;
	}

	if ((tofd = open(argv[2], WRITE_FLAGS, WRITE_PERMS)) == -1) {
		perror("Failed to create output file");
		return 1;
	}

	bytes = copyfile(fromfd, tofd);
	printf("%d bytes copid from %s to %s\n", bytes, argv[1], argv[2]);

	if (r_close(fromfd) == -1) {
		perror("Failed to close input file");
		return 1;
	}

	if (r_close(tofd) == -1) {
		perror("Failed to close output file");
		return 1;
	}

	return 0;
}
