#include "main.h"

/**
 * read_line - Reads a line from standard input.
 * @line: Pointer to buffer for storing the line.
 * @n: Pointer to size of the buffer.
 *
 * Return: Number of characters read, or -1 on failure or EOF.
 */
ssize_t read_line(char **line, size_t *n)
{
	ssize_t r = getline(line, n, stdin);

	if (r == -1)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "\n", 1);
	}

	return (r);
}
