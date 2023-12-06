#include "shell.h"


int main(int argc, char* argv[])
{
  char *line;
	char **args;
	int status = -1;
  do {
		printf("Prompt$ "); /* print prompt symbol */
		line = read_line(); /* read line from stdin */
		args = split_line(line); /* tokenize line */
		status = execute_args(args);
		/* avoid memory leaks */
		free(line);
		free(args);
		/* exit with status */
		if (status >= 0)
		{
			exit(status);
		}
	} while (status == -1);
}