#include "shell.h"

/**
 * print_prompt - prints shell prompt
 * @interactive: 1 if interactive shell
 */
void print_prompt(int interactive)
{
	if (interactive)
		printf("$ ");
	fflush(stdout);
}
