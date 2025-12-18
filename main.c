#include "main.h"

/**
 * main - Entry point for the simple shell program.
 *
 * Return: 0 on success, or another value on error.
 */
int main(void)
{
	char *line = NULL;
	size_t n = 0;
	ssize_t r;
	int last_status = 0;

	signal(SIGINT, handle_sigint);

	while (1)
	{
		display_prompt();

		r = read_line(&line, &n);
		if (r == -1)
			break;

		if (clean_line(line, r) == 0)
			continue;

		last_status = execute_command(line);
	}

	free(line);
	return (last_status);
}
