#ifndef _RESTART_H_
#define _RESTART_H_

#include <unistd.h>
#include <errno.h>

ssize_t r_read(int fd, void *buf, size_t size);
ssize_t r_write(int fd, void *buf, size_t size);
int r_close(int fd);

#endif /* _RESTART_H_ */
