#include "shell.h"
#include <stdio.h>

void print_not_found(shell_state_t *st, const char *cmd)
{
    fprintf(stderr, "%s: %d: %s: not found\n",
            st->prog, st->line_num, cmd);
}
