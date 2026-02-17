#include "shell.h"

#define MAX_ARGS 128

/**
 * free_argv - frees argv array
 * @argv: argv array to free
 *
 * Return: Nothing
 */
void free_argv(char **argv)
{
	free(argv);
}

/**
 * tokenize_line - splits a line into argv tokens
 * @line: input line (modified by strtok)
 *
 * Return: argv array (NULL-terminated) or NULL on failure
 */
char **tokenize_line(char *line)
{
	char **argv;
	size_t i = 0;
	char *tok;

	argv = malloc(sizeof(char *) * MAX_ARGS);
	if (argv == NULL)
		return (NULL);

	tok = strtok(line, " \t\n");
	while (tok != NULL && i < (MAX_ARGS - 1))
	{
		argv[i++] = tok;
		tok = strtok(NULL, " \t\n");
	}
	argv[i] = NULL;

	return (argv);
}
