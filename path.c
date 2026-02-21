#include "shell.h"

/**
 * check_in_dir - checks if command exists in a directory
 * @dir: directory path
 * @cmd: command name
 *
 * Return: full path string or NULL
 */
static char *check_in_dir(const char *dir, const char *cmd)
{
	size_t len = strlen(dir) + strlen(cmd) + 2;
	char *full_path = malloc(len);

	if (!full_path)
		return (NULL);

	sprintf(full_path, "%s/%s", dir, cmd);

	if (access(full_path, X_OK) == 0)
		return (full_path);

	free(full_path);
	return (NULL);
}

/**
 * get_path - finds executable path using PATH variable
 * @cmd: command name
 *
 * Return: full path string or NULL if not found
 */
char *get_path(const char *cmd)
{
	char *path_env;
	char *path_copy;
	char *token;
	char *res;

	if (strchr(cmd, '/'))
		return (access(cmd, X_OK) == 0 ? strdup(cmd) : NULL);

	path_env = getenv("PATH");
	if (!path_env || !*path_env)
		return (NULL);

	path_copy = strdup(path_env);
	if (!path_copy)
		return (NULL);

	token = strtok(path_copy, ":");
	while (token)
	{
		res = check_in_dir(token, cmd);
		if (res)
		{
			free(path_copy);
			return (res);
		}
		token = strtok(NULL, ":");
	}

	free(path_copy);
	return (NULL);
}
