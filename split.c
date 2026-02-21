#include "shell.h"

/**
 * split_line - wrapper for tokenize_line
 * @line: input line
 *
 * Return: argv array (tokens)
 *
 * Notes:
 *  - tokenize_line now returns **copies** of tokens,
 *    so freeing line early is safe.
 */
char **split_line(char *line)
{
    return tokenize_line(line);
}
