#include "shell.h"

/**
 * split_line - splits input line into arguments
 */
char **split_line(char *line)
{
	char **tokens;
	char *token;
	int i = 0;

	if (line == NULL)
		return (NULL);

	tokens = malloc(sizeof(char *) * 64);
	if (tokens == NULL)
		return (NULL);

	token = strtok(line, " \t\r\n");
	while (token != NULL)
	{
		tokens[i] = strdup(token);
		if (tokens[i] == NULL)
		{
			free_argv(tokens);
			return (NULL);
		}
		i++;
		token = strtok(NULL, " \t\r\n");
	}
	tokens[i] = NULL;

	return (tokens);
}
