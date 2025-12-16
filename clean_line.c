#include "main.h"

/**
 * clean_line - Cleans a line by removing the trailing newline character.
 * @line: Pointer to the input string to be cleaned.
 * @r: The number of characters read, typically from getline.
 *
 * This function checks if the last character in the input string is a newline
 * character ('\n'). If so, it replaces it with a null terminator ('\0') to
 * ensure the string is properly terminated and does not include the newline.
 * This is useful for processing user input or lines read from a file.
 *
 * Return: Always returns 0.
 */
int clean_line(char *line, ssize_t r)
{
	if (r > 0 && line[r - 1] == '\n')
		line[r - 1] = '\0';

	if (line[0] == '\0')
		return (0);

	return (1);
}
