#include "shell.h"


int execute_args(char **args)
{
	pid_t pid;
	int status;
	char *builtin_func_list[] = {
		"cd",
		"exit",
	};
	int (*builtin_func[])(char **) = {
		&own_cd,
		&own_exit,
	};
	pid = fork();
	if (pid ==  0)
	{
    long unsigned int i = 0;
		/* child process */
		for (; i < sizeof(builtin_func_list) / sizeof(char *); i++)
		{
			/* if there is a match execute the builtin command */
			if (strcmp(args[0], builtin_func_list[i]) == 0)
			{
				return ((*builtin_func[i])(args));
			}
		}
		if (execvp(args[0], args) == -1)
		{
			perror("error in new_process: child process");
		}
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
	{
		/* error forking */
		perror("error in new_process: forking");
	}
	else
	{
		/* parent process */
		do {
			waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
	return (-1);
}