#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

/* Shell state structure */
typedef struct shell_state
{
    char *prog;           /* program name */
    int interactive;      /* interactive mode flag */
    unsigned int line_num; /* line counter */
    int status;           /* last command exit status */
} shell_state_t;

/* Function declarations */
int run_shell(shell_state_t *st);
int execute_cmd(shell_state_t *st, char **argv);
char **tokenize_line(char *line);
void free_argv(char **argv);
char *get_path(const char *cmd);
void print_prompt(int interactive);
void print_not_found(shell_state_t *st, const char *cmd);

#endif /* SHELL_H */
