#include "shell.h"
#include <stdio.h>

/* Corrected function to match header */
void print_not_found(shell_state_t *st, char *cmd)
{
    fprintf(stderr, "%s: %d: %s: not found\n",
            st->prog, st->line_num, cmd);
}
