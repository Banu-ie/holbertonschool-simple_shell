#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

/* Shell state structure */
typedef struct shell_state
{
    char *prog;            /* program name */
    int interactive;       /* interactive mode flag */
    unsigned int line_num; /* line counter */
    int status;            /* last command exit status */
} shell_state_t;

/* Function prototypes */
void print_prompt(int interactive);
char **tokenize_line(char *line);
void free_argv(char **argv);
char *get_path(const char *cmd);
void print_not_found(shell_state_t *st, const char *cmd);
int execute_cmd(shell_state_t *st, char **argv);
int run_shell(shell_state_t *st);

#endif /* SHELL_H */
