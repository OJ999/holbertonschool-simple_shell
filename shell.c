#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define PROMPT "#cisfun$ "
#define BUFFER_SIZE 1024

/**
 * main - Entry point of the simple shell
 *
 * Return: Always 0 on success
 */
int main(void)
{
    char buffer[BUFFER_SIZE];
    ssize_t read_chars;
    pid_t child_pid;
    int status;

    while (1)
    {
        write(STDOUT_FILENO, PROMPT, strlen(PROMPT));

        read_chars = read(STDIN_FILENO, buffer, BUFFER_SIZE);
        if (read_chars == -1)
        {
            perror("read");
            exit(EXIT_FAILURE);
        }

        if (read_chars == 0)
        {
            write(STDOUT_FILENO, "\n", 1); /* Handle Ctrl+D (end of file) */
            exit(EXIT_SUCCESS);
        }

        buffer[read_chars - 1] = '\0'; /* Remove the newline character */

        child_pid = fork();

        if (child_pid == -1)
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }

        if (child_pid == 0)
        {
            /* Child process */
            char *args[] = {buffer, NULL};
            if (execve(buffer, args, NULL) == -1)
            {
                perror("execve");
                exit(EXIT_FAILURE);
            }
        }
        else
        {
            /* Parent process */
            if (waitpid(child_pid, &status, 0) == -1)
            {
                perror("waitpid");
                exit(EXIT_FAILURE);
            }
        }
    }

    return (0);
}
