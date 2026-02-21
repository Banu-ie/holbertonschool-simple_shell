#include "shell.h"

/**
 * find_in_path - searches PATH for a command
 * @cmd: command name
 *
 * Return: malloced full path or NULL
 */
char *find_in_path(const char *cmd)
{
	char *path_env, *path_copy, *dir, *full_path;
	size_t len;

	if (!cmd || strchr(cmd, '/'))
		return (cmd[0] ? strdup(cmd) : NULL);

	path_env = getenv("PATH");
	if (!path_env)
		return (NULL);

	path_copy = strdup(path_env);
	if (!path_copy)
		return (NULL);

	dir = strtok(path_copy, ":");
	while (dir)
	{
		len = strlen(dir) + 1 + strlen(cmd) + 1;
		full_path = malloc(len);
		if (!full_path)
		{
			free(path_copy);
			return (NULL);
		}
		snprintf(full_path, len, "%s/%s", dir, cmd);
		if (access(full_path, X_OK) == 0)
		{
			free(path_copy);
			return (full_path);
		}
		free(full_path);
		dir = strtok(NULL, ":");
	}

	free(path_copy);
	return (NULL);
}
