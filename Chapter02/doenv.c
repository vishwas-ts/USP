#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>

extern char **environ;
int environ_size = 0;

void printev(void) {
	printf("The environment variables are:\n");
	for (int i = 0; environ[i] != NULL; i++) {
		printf("%s\n", environ[i]);
	}

}

void clearev(void) {
	environ = (char**) NULL;
	environ_size = 0;
}

int checkev(char* data) {
	char* str = NULL;

	int i;
	int ret;

	str = malloc(strlen(data) + 1); 
	if (str == NULL) {
		fprintf(stderr, "Unable to allocate memory for tokens\n");
		return -1;
	}
	strcpy(str, data);

	/* The the name from the name=value pair */
	str = strtok(str, "=");
	size_t str_len = strlen(str);

	for ( i = 0; i < environ_size; i++) {
		if (strncmp(str, environ[i], str_len) == 0) { 
			ret = i;
			break;
		}
	}
	if (i == environ_size)
		ret = environ_size;

	if (str != NULL) {
		free(str);
	}
	return ret;
}

int replaceev(int i, char *cmd) {
	char *str = NULL;

	str = malloc(strlen(cmd) + 1);
	strcpy(str, cmd);
	if (str == NULL)
		return -1;
	environ[i] = str;

	return 0;
}

char *localenviron[15] = {};
int localenvironsize = 0;

int addev(char *data) {
	if (localenvironsize > 14)
		return -1;

	char * str = malloc (strlen(data) + 1);
	if (str == NULL) {
		return -1;
	}
	strcpy(str, data);

	localenviron[localenvironsize] = str;
	localenvironsize++;
	return 0; 
}


int concatev(void) {
	int i,j;
	int total_size = localenvironsize + environ_size;
	if (total_size == 0)
		return 0;

	char ** new_environ = (char **) (malloc(sizeof(char *) * (total_size + 1)));
	if (new_environ == NULL)
		return -1;

	for (int i = 0; i < environ_size; i++) {
		new_environ[i] = environ[i];
	}

	for (i = environ_size, j = 0; i < total_size; i++, j++) {
		new_environ[i] = localenviron[j];
	}
	new_environ[i] = NULL;
	environ = new_environ;

	return 0;
}




int main(int argc, char *argv[]) {
	int i = 0;

	for (i = 0; environ[i] != NULL; i++) 
		/* Get environment variable count*/ ;
	environ_size = i;
	
	if (argc == 1) {
		printev();
		return 0;
	}

	/*
	if ((argc > 1) && ((strcmp(argv[1], "-i")) && (strcmp(argv[1], "utility")))) {
		fprintf(stderr, "Usage: doenv [-i] [name=value] ... [utility [argument ...]]\n");
		return -1;
	}
	*/

	i = 1;	
	if (!strcmp(argv[1], "-i")) {
		clearev();
		i = 2;
	}

		
	while ((i < argc) && strcmp(argv[i], "utility") ) {
		int evexist = checkev(argv[i]);

		if ((evexist >= 0) && (evexist < environ_size))
			replaceev(evexist, argv[i]);
		else if (evexist == -1)
			exit(1);
		else	
			addev(argv[i]);
		i++;
	}

	concatev();

	if (i == argc) {
		printev();
		return 0;
	}
	i++;

	char command[MAX_CANON] = {};

	strcpy(command, argv[i]);
	i++;

	while (i < argc) {
		strcat(command, " ");
		strcat(command, argv[i]);
		i++;
	}

	if (system(command) == -1) {
		perror("Unable to execute command") ;
	}

	return 0;
}


