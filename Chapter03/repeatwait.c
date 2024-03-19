#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

pid_t r_wait(int *statloc) {
	int retval;

	while (((retval = wait(statloc)) == -1) && (errno == EINTR));
	return retval;
}

void show_return_status(void) {
	pid_t childpid;
	int status;

	childpid = r_wait(&status);
	if (childpid == -1)
		perror("Failed to wait for child");
	else if (WIFEXITED(status) && !WEXITSTATUS(status))
		printf("Child %ld Terminated normally\n", (long)childpid);
	else if (WIFEXITED(status))
		printf("Child %ld terminated with return status %d\n",
				(long)childpid, WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		printf("Child %ld terminated due to uncaught signal %d\n",
				(long)childpid, WTERMSIG(status));
	else if (WIFSTOPPED(status))
		printf("Child %ld stopped due to signal %d\n",
				(long)childpid, WSTOPSIG(status));
}	 
