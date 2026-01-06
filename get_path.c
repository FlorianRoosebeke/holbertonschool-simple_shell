#include "main.h"

/**
 * get_path - Retrieves and tokenizes the PATH environment variable.
 * @envp: Environment variables.
 *
 * Return: Array of PATH directories, or NULL on error.
 *
 * Description: This function searches for the PATH environment variable,
 *              tokenizes it by '=' and ':', and returns each directory.
 */

char **get_path(char **envp)
{

	int i = 0, j = 0;
	char *path_copy, *delimiters = "=:", *token, **tokens;

	tokens = malloc(sizeof(char *) * 128);
	if (tokens == NULL)
		return (NULL);

	while (envp[i])
	{
		if (strncmp(envp[i], "PATH=", 5) == 0)
		{
			path_copy = strdup(envp[i]);
			if (path_copy == NULL)
			{
				free(tokens);
				return (NULL);
			}
			break;
		}
		i++;
	}

	tokens[0] = path_copy;
	j = 1;
	token = strtok(path_copy, delimiters);
	while (token != NULL && j < 127)
	{
		token = strtok(NULL, delimiters);
		tokens[j] = token;
		j++;
	}
	tokens[j] = NULL;
	return (tokens);
}
