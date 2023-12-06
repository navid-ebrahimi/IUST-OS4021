#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
#include<dirent.h>
#include<pthread.h>

#define MAX_INPUT_LEN 256

struct SearchArg {
	char dirname[MAX_INPUT_LEN];
	char query[MAX_INPUT_LEN];
};

void* searchThread(void* args);
void searchFileOrDir(const char *currentDir, const char *targetName);


int main(int argc, char* argv[]) {
	char* QUERY = (char*)malloc(MAX_INPUT_LEN);
	char* DIR = (char*)malloc(MAX_INPUT_LEN);

	strcpy(DIR, argv[1]);
	strcpy(QUERY, argv[2]);

	if (DIR[strlen(DIR) - 1] != '/') {
		printf("Enter the path with the last for slash /.\n");
		exit(EXIT_FAILURE);
	}

	pthread_t th;
	struct SearchArg *arg = (struct SearchArg*)malloc(sizeof(struct SearchArg));
	
	strcpy(arg->dirname, DIR);
	strcpy(arg->query, QUERY);
	
	if (pthread_create(&th, NULL, searchThread, (void*)arg) != 0) {
		perror("[-] failed to create the main search thread");
		exit(EXIT_FAILURE);
	}


	if (pthread_join(th, NULL) != 0) {
		perror("[-] failed to join the main search thread");
		exit(EXIT_FAILURE);
	}

	return 0;
}


void searchFileOrDir(const char *currentDir, const char *targetName) {
	DIR *dir = opendir(currentDir);
	if (dir == NULL) {
		perror("[-] can't open a directory");
		printf("No such directory: %s\n", currentDir);
		exit(EXIT_FAILURE);
	}
	
	struct dirent *entry;
	while ((entry = readdir(dir)) != NULL) {
		if (entry->d_type == DT_DIR) {
			// check if the directory is . or ..
			if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
				continue;
			}

			// call a new thread
			pthread_t th;
			char* path = (char*)malloc(sizeof(char) * MAX_INPUT_LEN);
			sprintf(path, "%s%s/", currentDir, entry->d_name);
			struct SearchArg *arg = (struct SearchArg*)malloc(sizeof(struct SearchArg));
			
			strcpy(arg->dirname, path);
			strcpy(arg->query, targetName);

			if (pthread_create(&th, NULL, searchThread, (void*)arg) != 0) {
				perror("[-] Failed to create a thread");
				exit(EXIT_FAILURE);
			}

		}

		else if (strcmp(entry->d_name, targetName) == 0) {
			// lock stdout to avoid interfering between threads
			flockfile(stdout);
			printf("[+] Found:\n %s%s\n\n", currentDir, targetName);
		}
	}

	// unlock stdout for other threads
	funlockfile(stdout);

	closedir(dir);
}


void* searchThread(void* args) {
	struct SearchArg *search_args = (struct SearchArg*)args;
	searchFileOrDir(search_args->dirname, search_args->query);
	pthread_exit(NULL);
}
