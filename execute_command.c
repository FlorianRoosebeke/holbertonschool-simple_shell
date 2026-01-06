#include "main.h"

/**
 * exec_cmd - Forks and executes a command
 * @cmd: Command path to execute
 * @argv: Arguments array
 * @envp: Environment variables
 */
void exec_cmd(char *cmd, char **argv, char **envp)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == 0)
	{
		execve(cmd, argv, envp);
		perror("Error");
		exit(1);
	}
	else if (pid > 0)
		wait(&status);
	else
		perror("fork");
}

/**
 * exec_from_path - Searches and executes command from PATH
 * @argv: Arguments array
 * @envp: Environment variables
 */
void exec_from_path(char **argv, char **envp)
{
	char full_path[1024], **paths;
	int i = 0;

	paths = get_path(envp);
	while (paths[i])
	{
		snprintf(full_path, sizeof(full_path), "%s/%s", paths[i], argv[0]);
		if (access(full_path, X_OK) == 0)
		{
			exec_cmd(full_path, argv, envp);
			free(paths[0]);
			free(paths);
			return;
		}
		i++;
	}
	fprintf(stderr, "./hsh: 1: %s: not found\n", argv[0]);
	free(paths[0]);
	free(paths);
}

/**
 * execute_command - Forks and executes a command using execve.
 * @line: The command line to execute.
 * @envp: Environment variables.
 */
void execute_command(char *line, char **envp)
{
	char *argv[1024];

	if (splitCommand(line, argv) == 0)
		return;

	if (strcmp(argv[0], "exit") == 0)
	{
		free(line);
		exit(0);
	}
	if (strcmp(argv[0], "env") == 0)
	{
		handle_env(envp);
		return;
	}

	if (strchr(argv[0], '/') != NULL)
	{
		if (access(argv[0], X_OK) == 0)
		{
			exec_cmd(argv[0], argv, envp);
			return;
		}
		fprintf(stderr, "./hsh: 1: %s: not found\n", argv[0]);
		return;
	}

	exec_from_path(argv, envp);
}
