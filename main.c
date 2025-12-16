#include "main.h"

/**
 * main - Entry point for the simple shell program.
 *
 * Return: 0 on success, or another value on error.
 */
int main(void)
{
	char *lineprt = NULL;
	size_t n = 0;
	ssize_t r;
	pid_t pid;
	int status;
	char *argv[2];

	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "$ ", 2);
		r = getline(&lineprt, &n, stdin);
		if (r == -1)
		{
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "\n", 2);
			break;
		}
		if (r > 0 && lineprt[r - 1] == '\n')
			lineprt[r - 1] = '\0';
		if (lineprt[0] == '\0')
			continue;

		pid = fork();
		if (pid == 0)
		{
			argv[0] = lineprt;
			argv[1] = NULL;
			execve(lineprt, argv, NULL);
			perror("Error");
			exit(1);
		}
		else if (pid > 0)
			wait(&status);
		else
			perror("fork");
	}
	free(lineprt);
	return (0);
}
