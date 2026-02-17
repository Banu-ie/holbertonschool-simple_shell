#include "shell.h"

/**
 * execute_cmd - forks and executes a command (full path, no args)
 * @st: shell state
 * @cmd: command to execute
 *
 * Return: 0 always
 */
int execute_cmd(shell_state_t *st, char *cmd)
{
	pid_t pid;
	int status;
	char *argv_exec[2];

	if (access(cmd, X_OK) == -1)
	{
		print_not_found(st, cmd);
		return (0);
	}

	pid = fork();
	if (pid == -1)
	{
		perror(st->prog);
		return (0);
	}

	if (pid == 0)
	{
		argv_exec[0] = cmd;
		argv_exec[1] = NULL;

		execve(cmd, argv_exec, environ);
		perror(st->prog);
		_exit(127);
	}

	waitpid(pid, &status, 0);
	return (0);
}

/**
 * run_shell - main loop of the shell (0.1)
 * @st: shell state
 *
 * Return: 0 on success
 */
int run_shell(shell_state_t *st)
{
	char *line = NULL, *cmd = NULL;
	size_t len = 0;
	ssize_t nread;

	while (1)
	{
		print_prompt(st->interactive);
		nread = getline(&line, &len, stdin);

		if (nread == -1)
		{
			free(line);
			return (0);
		}

		st->line_num++;

		cmd = strtok(line, " \t\n");
		if (cmd == NULL)
			continue;

		execute_cmd(st, cmd);
	}
}
