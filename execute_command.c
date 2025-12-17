#include "main.h"

/**
 * execute_command - Forks and executes a command using execve.
 * @line: The command line to execute.
 */
void execute_command(char *line)
{
	pid_t pid;
	int status;
	char *argv[128];

	if (splitCommand(line, argv) == 0)
		return;

	if (strcmp(argv[0], "exit") == 0)
	{
		free(line);
		exit(0);
	}
	if (strcmp(argv[0], "env") == 0)
	{
		handle_env();
		return;
	}

	pid = fork();
	if (pid == 0)
	{
		execve(argv[0], argv, NULL);
		perror("Error");
		exit(1);
	}
	else if (pid > 0)
		wait(&status);
	else
		perror("fork");
}
