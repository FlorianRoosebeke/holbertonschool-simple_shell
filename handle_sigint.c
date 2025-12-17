#include "main.h"



/**
 * handle_sigint - Handles the SIGINT signal (Ctrl+C).
 * @signal: The signal number.
 *
 * This function writes a new prompt to the standard output
 * when the user presses Ctrl+C.
 */
void handle_sigint(int signal)
{
	(void)signal;

	write(STDOUT_FILENO, "\n$ ", 3);
}
