#ifndef MAIN_H
#define MAIN_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <features.h>
#include <signal.h>


void display_prompt(void);
ssize_t read_line(char **line, size_t *n);
int clean_line(char *line, ssize_t r);
int execute_command(char *line);
int splitCommand(char *input, char **argv);
void handle_sigint(int signal);

#endif
