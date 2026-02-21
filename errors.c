#include "shell.h"

/**
 * print_not_found - prints command not found error
 * @st: shell state
 * @cmd: command name
 */
void print_not_found(shell_state_t *st, const char *cmd)
{
	fprintf(stderr, "%s: %lu: %s: not found\n",
		st->prog, st->line_num, cmd);
}
