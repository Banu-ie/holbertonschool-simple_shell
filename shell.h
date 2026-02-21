#ifndef SHELL_H
#define SHELL_H

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

extern char **environ;

/**
 * struct shell_state - shell runtime state
 * @prog: program name (argv[0])
 * @line_num: command counter
 * @interactive: 1 if interactive, 0 otherwise
 */
typedef struct shell_state
{
	char *prog;
	unsigned long line_num;
	int interactive;
} shell_state_t;

void print_prompt(int interactive);
void print_not_found(shell_state_t *st, const char *cmd);

char **tokenize_line(char *line);
void free_argv(char **argv);

int run_shell(shell_state_t *st);
int execute_cmd(shell_state_t *st, char **argv);
char *find_in_path(char *cmd);

#endif /* SHELL_H */
