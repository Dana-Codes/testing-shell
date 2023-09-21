#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024

int main()
{
    char *buffer;
    size_t bufsize = BUFFER_SIZE;
    ssize_t characters_read;

    buffer = (char *)malloc(bufsize * sizeof(char));
    if (!buffer)
    {
        perror("malloc failed");
        exit(EXIT_FAILURE);
    }

    while (1)
    {
        printf("#cisfun$ ");
        characters_read = getline(&buffer, &bufsize, stdin);

        if (characters_read == -1)
        {
            printf("\n");
            break;
        }

        // Remove the newline character
        if (buffer[characters_read - 1] == '\n')
            buffer[characters_read - 1] = '\0';

        // Fork a child process
        pid_t pid = fork();

        if (pid == -1)
        {
            perror("fork failed");
            exit(EXIT_FAILURE);
        }
        if (pid == 0)
        {
            // Child process
            execve(buffer, NULL, NULL);
            perror("execve failed");
            exit(EXIT_FAILURE);
        }
        else
        {
            // Parent process
            wait(NULL); // Wait for the child to complete
        }
    }

    free(buffer);
    return 0;
}
