#include "shell.h"

/**
 * print_prompt - prints prompt if shell is interactive
 * @interactive: 1 if interactive, 0 otherwise
 *
 * Return: Nothing
 */
void print_prompt(int interactive)
{
	if (interactive)
		write(STDOUT_FILENO, "($) ", 4);
}

/**
 * print_not_found - prints error message for command not found
 * @st: shell state
 * @cmd: command entered by user
 *
 * Return: Nothing
 */
void print_not_found(shell_state_t *st, const char *cmd)
{
	fprintf(stderr, "%s: %lu: %s: not found\n", st->prog, st->line_num, cmd);
}
