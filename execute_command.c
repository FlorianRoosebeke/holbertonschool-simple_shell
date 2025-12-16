#include "main.h"

/**
 * execute_command - Forks and executes a command using execve.
 * @line: The path to the command to execute.
 */
void execute_command(char *line)
{
	pid_t pid;
	int status;
	char *argv[2];

	pid = fork();
	if (pid == 0)
	{
		argv[0] = line;
		argv[1] = NULL;
		execve(line, argv, NULL);
		perror("Error");
		exit(1);
	}
	else if (pid > 0)
		wait(&status);
	else
		perror("fork");
}
