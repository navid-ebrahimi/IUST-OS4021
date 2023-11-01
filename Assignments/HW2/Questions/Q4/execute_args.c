#include "shell.h"


int execute_args(char **args)
{
	pid_t pid;
	int status;
	char *builtin_func_list[] = {
		// you should add something here
		"exit",
	};
	int (*builtin_func[])(char **) = {
		// you should add something here
		&own_exit,
	};

	long unsigned int i = 0;
	for (; i < sizeof(builtin_func_list) / sizeof(char *); i++)
	{
		/* if there is a match execute the builtin command */
		if (strcmp(args[0], builtin_func_list[i]) == 0)
		{
			return ((*builtin_func[i])(args));
		}
	}

	// TODO
	return (-1); // this status code means everything is ok
}