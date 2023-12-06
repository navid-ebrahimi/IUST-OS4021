/*---LIBRARIES---*/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

#define TOK_DELIM " \t\r\n\a\""

/* Necessary functions */
char *read_line(void);
char **split_line(char *line);
int execute_args(char **args);

/*---Builtin func---*/
int own_cd(char **args);
int own_exit(char **args);