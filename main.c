#include "shell.h"

/**
 * main - entry point for simple shell (0.1)
 * @ac: argument count (unused)
 * @av: argument vector
 *
 * Return: 0 on success
 */
int main(int ac, char **av)
{
	shell_state_t st;

	(void)ac;
	st.prog = av[0];
	st.line_num = 0;
	st.interactive = isatty(STDIN_FILENO);

	return (run_shell(&st));
}
