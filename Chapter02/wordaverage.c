#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define WORD_DELIMITERS " "
#define LINE_DELIMITERS "\n"

static int wordcount(char *s) {
	int count = 1;
	char *lasts;

	if (strtok_r(s, WORD_DELIMITERS, &lasts) == NULL)
		return 0;
	
	while (strtok_r(NULL, WORD_DELIMITERS, &lasts) != NULL)
		count++;

	return count;
}

double wordaverage(char *s) {
	char *lasts;
	int linecount = 1;

	char *nextline;

	int words;

	nextline = strtok_r(s, LINE_DELIMITERS, &lasts);
	if (nextline == NULL)
		return 0.0;

	words = wordcount(nextline);
	while ((nextline = strtok_r(NULL, LINE_DELIMITERS, &lasts)) != NULL) {
		words += wordcount(nextline);
		linecount++;
	}

	return (double)words/linecount;
}


int main(int argc, char* argv[]) {
	int i = 0;
	char c;
	char words[4096];

	while ((c = getchar())!= EOF)
		words[i++] = c;

	printf("Word average for the given file is: %f\n", wordaverage(words)); 
	return 0;
}

