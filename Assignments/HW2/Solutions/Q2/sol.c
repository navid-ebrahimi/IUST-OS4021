#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

#define MAX_FILE_NAME_SIZE 256


int countOccurrences(const char *filename, const char *query) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("fopen");
        return -1;
    }

    int count = 0;
    char buffer[1024];

    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        char *pos = buffer;

        while ((pos = strstr(pos, query)) != NULL) {
            ++count;
            pos += strlen(query);
        }
    }

    fclose(file);
    return count;
}


int main(int argc, char* argv[]) {
	if (argc < 3) {
		printf("[-] The pattern is like this:\n");
		printf("search <file> <parameter1> <parameter2> ...\n");
		exit(1);
	}

	char* filename = (char*)malloc(sizeof(char) * MAX_FILE_NAME_SIZE);
	strcpy(filename, argv[1]);

	char** queries = (char**)malloc(sizeof(char*) * argc - 2);
	for (int i = 2; i < argc; i++) {
		queries[i-2] = (char*)malloc(sizeof(char) * MAX_FILE_NAME_SIZE);
		strcpy(queries[i-2], argv[i]);
	}

	pid_t processes[argc - 2];

	for (int i = 0; i < argc - 2; i++) {
		pid_t pid = fork();

		if (pid < 0) {
			printf("[-] Error in creating a new process");

		} else if (pid == 0) {
			int count = countOccurrences(filename, queries[i]);
			printf("%s: %d\n", queries[i], count);
			exit(count);
		} else {
			// parent process
			processes[i] = pid;
		}
	}


	int total = 0;
	for (int i = 0; i < argc - 2; i++) {
		int status;
		waitpid(processes[i], &status, 0);

		if (WIFEXITED(status)) {
			int count = WEXITSTATUS(status);
			total += count;
		}
	}

	printf("The total occurrences: %d\n", total);

	return 0;
}
