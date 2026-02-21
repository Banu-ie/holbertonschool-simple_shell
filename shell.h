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
    char *prog;       /* program name */
    int interactive;  /* interactive mode flag */
    int line_num;     /* current line number */
} shell_state_t;

/* Function declarations */
void print_prompt(int interactive);
char **tokenize_line(char *line);
void free_argv(char **argv);
void print_not_found(shell_state_t *st, const char *cmd);
int execute_cmd(shell_state_t *st, char **argv);
int run_shell(shell_state_t *st);

/* Added function to find command in PATH */
char *get_path(const char *cmd);

#endif /* SHELL_H */
