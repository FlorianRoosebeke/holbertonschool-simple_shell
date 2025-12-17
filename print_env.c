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
		printf("%s\n", environ[i]);
		i++;
	}
}
