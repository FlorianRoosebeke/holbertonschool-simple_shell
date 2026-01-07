#include "main.h"

/**
 * main - Entry point for the simple shell program.
 * @argc: Argument count (unused).
 * @argv: Argument vector (unused).
 * @envp: Environment variables.
 *
 * Return: 0 on success, or another value on error.
 */
int main(int argc, char **argv, char **envp)
{
	char *line = NULL;
	size_t n = 0;
	ssize_t r;
	int last_status = 0;

	(void)argc;
	(void)argv;

	signal(SIGINT, handle_sigint);

	while (1)
	{
		display_prompt();

		r = read_line(&line, &n);
		if (r == -1)
			break;

		if (clean_line(line, r) == 0)
			continue;

		last_status = execute_command(line, &line, envp);
	}

	free(line);
	return (last_status);
}
