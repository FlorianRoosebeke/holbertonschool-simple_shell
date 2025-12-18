#include "main.h"

/**
 * handle_env - prints the environment variables
 *
 * Return: void
 */
void handle_env(void)
{

	int i = 0;

	while (environ[i] != NULL)
	{
		write(STDOUT_FILENO, environ[i], strlen(environ[i]));
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}
}
