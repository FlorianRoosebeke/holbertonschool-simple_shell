#include "main.h"

/**
 * exec_cmd - Forks and executes a command
 * @cmd: Command path to execute
 * @argv: Arguments array
 * @envp: Environment variables
 * @line_ptr: Pointer to line buffer (to free in child)
 *
 * Return: Exit status of the command
 */
int exec_cmd(char *cmd, char **argv, char **envp, char **line_ptr)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == 0)
	{
		execve(cmd, argv, envp);
		perror("Error");
		if (*line_ptr)
			free(*line_ptr);
		exit(127);
	}
	else if (pid > 0)
	{
		wait(&status);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
	}
	else
		perror("fork");
	return (127);
}

/**
 * exec_from_path - Searches and executes command from PATH
 * @argv: Arguments array
 * @envp: Environment variables
 * @line_ptr: Pointer to line buffer (to free in child)
 *
 * Return: Exit status of the command, or 127 if not found
 */
int exec_from_path(char **argv, char **envp, char **line_ptr)
{
	char full_path[1024], **paths = get_path(envp);
	int i = 0, status;
	pid_t pid;

	while (paths && paths[i])
	{
		snprintf(full_path, sizeof(full_path), "%s/%s", paths[i], argv[0]);
		if (access(full_path, X_OK) == 0)
			break;
		i++;
	}
	if (!paths || !paths[i])
	{
		fprintf(stderr, "./hsh: 1: %s: not found\n", argv[0]);
		if (paths)
			free(paths[0]), free(paths);
		return (127);
	}
	pid = fork();
	if (pid == 0)
	{
		if (*line_ptr)
			free(*line_ptr);
		if (paths)
			free(paths[0]), free(paths);
		execve(full_path, argv, envp);
		exit(127);
	}
	wait(&status);
	if (paths)
		free(paths[0]), free(paths);
	return (WIFEXITED(status) ? WEXITSTATUS(status) : 127);
}

/**
 * execute_command - Forks and executes a command using execve.
 * @line: The command line to execute.
 * @line_ptr: Pointer to line buffer (to free in child)
 * @envp: Environment variables.
 *
 * Return: Exit status of the command
 */
int execute_command(char *line, char **line_ptr, char **envp)
{
	char *argv[1024];

	if (splitCommand(line, argv) == 0)
		return (0);

	if (strcmp(argv[0], "exit") == 0)
	{
		free(line);
		exit(0);
	}
	if (strcmp(argv[0], "env") == 0)
	{
		handle_env(envp);
		return (0);
	}

	if (strchr(argv[0], '/') != NULL)
	{
		if (access(argv[0], X_OK) == 0)
			return (exec_cmd(argv[0], argv, envp, line_ptr));
		fprintf(stderr, "./hsh: 1: %s: not found\n", argv[0]);
		return (127);
	}

	return (exec_from_path(argv, envp, line_ptr));
}
