#include "shell.h"
#include <stdio.h>

/**
 * print_not_found - prints command not found message
 * @st: shell state
 * @cmd: command
 */
void print_not_found(shell_state_t *st, const char *cmd)
{
	fprintf(stderr, "%s: %d: %s: not found\n",
			st->prog, st->line_num, cmd);
}
