#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void display_prompt(void);
ssize_t read_line(char **line, size_t *n);
int clean_line(char *line, ssize_t r);
void execute_command(char *line);

#endif
