#include "shell.h"

char *read_line(void)
{
	char *line = NULL;
	size_t bufsize = 0;

	if (getline(&line, &bufsize, stdin) == -1) /* if getline fails */
	{
		if (feof(stdin)) /* test for the eof */
		{
			free(line); /* avoid memory leaks when ctrl + d */
			exit(EXIT_SUCCESS); /* we recieved an eof */
		}
		else
		{
			free(line); /* avoid memory leaks when getline fails */
			perror("error while reading the line from stdin");
			exit(EXIT_FAILURE);
		}
	}
	return (line);
}