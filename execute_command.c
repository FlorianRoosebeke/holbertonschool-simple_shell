#include "main.h"

/**
 * execute_command - Forks and executes a command using execve.
 * @line: The command line to execute.
 * @envp: Environment variables.
 */
void execute_command(char *line, char **envp)
{
	pid_t pid;
	int status, i = 0;
	char full_path[1024], *argv[1024], **paths;

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

	paths = get_path(envp);
	i = 1;
	while (paths[i])
	{
		snprintf(full_path, sizeof(full_path), "%s/%s", paths[i], argv[0]);
		if (access(full_path, X_OK) == 0)
		{
			pid = fork();
			if (pid == 0)
			{
				execve(full_path, argv, envp);
				perror("Error");
				exit(1);
			}
			else if (pid > 0)
				wait(&status);
			else
				perror("fork");
			free(paths[0]);
			free(paths);
			return;
		}
		i++;
	}
	printf("%s: command not found\n", argv[0]);
	free(paths[0]);
	free(paths);
}
