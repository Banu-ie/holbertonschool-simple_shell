#include "shell.h"

/**
 * split_line - wrapper for tokenize_line
 * @line: input line
 *
 * Return: array of tokens
 */
char **split_line(char *line)
{
	return (tokenize_line(line));
}
