// src/osh.c
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINE 80 /* The maximum length command */

int main(void) {
    char *args[MAX_LINE / 2 + 1]; /* command line arguments */
    char input[MAX_LINE];
    int should_run = 1;

    while (should_run) {
        printf("osh>");
        fflush(stdout);

        // 1) Get input from user
        if (fgets(input, MAX_LINE, stdin) == NULL) break;
        input[strcspn(input, "\n")] = 0; // Remove newline

        // 2) Tokenize input (Turn "ls -l" into ["ls", "-l", NULL])
        int i = 0;
        args[i] = strtok(input, " ");
        while (args[i] != NULL) {
            i++;
            args[i] = strtok(NULL, " ");
        }

        if (args[0] == NULL) continue;               // Ignore empty input
        if (strcmp(args[0], "exit") == 0) break;     // Built-in exit

        // (4) If the command included '&', parent will NOT wait
        int background = 0;
        if (i > 0 && args[i - 1] != NULL && strcmp(args[i - 1], "&") == 0) {
            background = 1;
            args[i - 1] = NULL; // Remove '&' from args
        }

        // (1) Fork a child process
        pid_t pid = fork();

        if (pid < 0) {
            fprintf(stderr, "Fork Failed\n");
            return 1;
        } else if (pid == 0) {
            // CHILD PROCESS
            // (2) Invoke execvp()
            // execvp only returns if it fails
            if (execvp(args[0], args) == -1) {
                perror("Command not found");
            }
            exit(1);
        } else {
            // PARENT PROCESS
            // (3) Wait for the child (unless background)
            if (!background) {
                waitpid(pid, NULL, 0);
            } else {
                // optional: show background pid
                printf("[background pid %d]\n", pid);
            }
        }
    }

    return 0;
}
