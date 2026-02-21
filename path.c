#include "shell.h"
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

extern char **environ;

/**
 * get_path - finds executable path using PATH variable
 * @cmd: command name
 *
 * Return: full path string or NULL if not found
 */
char *get_path(const char *cmd)
{
	char *path_env = NULL;
	char *path_copy, *token;
	char *full_path;
	size_t len;
	int i;

	if (strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return strdup(cmd);
		return NULL;
	}

	for (i = 0; environ[i]; i++)
	{
		if (strncmp(environ[i], "PATH=", 5) == 0)
		{
			path_env = environ[i] + 5;
			break;
		}
	}

	if (!path_env || path_env[0] == '\0')
		return NULL;

	path_copy = strdup(path_env);
	if (!path_copy)
		return NULL;

	token = strtok(path_copy, ":");
	while (token)
	{
		len = strlen(token) + strlen(cmd) + 2;
		full_path = malloc(len);
		if (!full_path)
		{
			free(path_copy);
			return NULL;
		}

		sprintf(full_path, "%s/%s", token, cmd);

		if (access(full_path, X_OK) == 0)
		{
			free(path_copy);
			return full_path;
		}

		free(full_path);
		token = strtok(NULL, ":");
	}

	free(path_copy);
	return NULL;
}
