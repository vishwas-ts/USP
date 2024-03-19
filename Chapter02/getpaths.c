#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define PATH_DELIMITERS ":"

extern int make_argv_delim(const char *s, const char *delimiters,char ***argvp);

char **getpaths(void) {
	char **myargv;
	char *path;

	path = getenv("PATH");
	if (make_argv_delim(path, PATH_DELIMITERS, &myargv) == -1)
		return NULL;
	else
		return myargv;
}

int main(int argc, char *argv[]) {
	char ** path_list;

	path_list = getpaths();

	printf("The path list follows:\n");
	for (int i = 0; path_list[i] != NULL; i++) {
		printf("%d.%s\n", i, path_list[i]);
	}

	return 0;
}
