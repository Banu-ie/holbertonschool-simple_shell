#include "shell.h"

/**
 * get_path_env - retrieves PATH value
 */
char *get_path_env(void)
{
	int i = 0;

	while (environ[i])
	{
		if (strncmp(environ[i], "PATH=", 5) == 0)
			return (environ[i] + 5);
		i++;
	}
	return (NULL);
}

/**
 * build_full_path - builds full path from dir and command
 */
char *build_full_path(char *dir, char *cmd)
{
	char *full;
	size_t len;

	len = strlen(dir) + strlen(cmd) + 2;

	full = malloc(len);
	if (full == NULL)
		return (NULL);

	strcpy(full, dir);
	strcat(full, "/");
	strcat(full, cmd);

	return (full);
}

/**
 * find_in_path - searches command inside PATH
 */
char *find_in_path(char *cmd)
{
	char *path_env, *path_copy, *dir, *full;

	if (cmd == NULL)
		return (NULL);

	if (strchr(cmd, '/'))
		return (NULL);

	path_env = get_path_env();
	if (path_env == NULL || *path_env == '\0')
		return (NULL);

	path_copy = strdup(path_env);
	if (path_copy == NULL)
		return (NULL);

	dir = strtok(path_copy, ":");
	while (dir != NULL)
	{
		full = build_full_path(dir, cmd);
		if (full != NULL && access(full, X_OK) == 0)
		{
			free(path_copy);
			return (full);
		}

		free(full);
		dir = strtok(NULL, ":");
	}

	free(path_copy);
	return (NULL);
}
