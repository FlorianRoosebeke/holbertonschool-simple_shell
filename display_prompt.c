#include "main.h"

/**
 * display_prompt - Displays the shell prompt if input is from a terminal.
 */
void display_prompt(void)
{
	if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO, "$ ", 2);
}
