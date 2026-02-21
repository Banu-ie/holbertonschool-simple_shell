#include "shell.h"

/**
 * find_in_path - searches PATH for a command
 * @cmd: command name
 *
 * Return: malloced full path or NULL
 */
char *find_in_path(const char *cmd)
{
	char *path_env, *path_copy, *dir, *saveptr;
	char *full_path;
	size_t len;

	if (!cmd)
		return (NULL);

	/* If command contains '/', check directly */
	if (strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (strdup(cmd));
		return (NULL);
	}

	path_env = getenv("PATH");
	if (!path_env || path_env[0] == '\0')
		return (NULL);

	path_copy = strdup(path_env);
	if (!path_copy)
		return (NULL);

	dir = strtok_r(path_copy, ":", &saveptr);
	while (dir)
	{
		len = strlen(dir) + strlen(cmd) + 2;
		full_path = malloc(len);
		if (!full_path)
		{
			free(path_copy);
			return (NULL);
		}

		sprintf(full_path, "%s/%s", dir, cmd);

		if (access(full_path, X_OK) == 0)
		{
			free(path_copy);
			return (full_path);
		}

		free(full_path);
		dir = strtok_r(NULL, ":", &saveptr);
	}

	free(path_copy);
	return (NULL);
}
