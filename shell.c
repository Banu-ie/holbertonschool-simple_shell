#include "shell.h"
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

extern char **environ;

/**
 * handle_child_exit - handle child process exit status
 * @st: shell state
 * @status: waitpid status
 */
void handle_child_exit(shell_state_t *st, int status)
{
	if (WIFEXITED(status))
		st->status = WEXITSTATUS(status);
	else
		st->status = 127;
}

/**
 * execute_cmd - forks and executes a command
 * @st: shell state
 * @argv: argument vector
 *
 * Return: 0 on success, 127 if not found
 */
int execute_cmd(shell_state_t *st, char **argv)
{
	pid_t pid;
	int status;
	char *cmd_path;

	if (!argv || !argv[0])
		return (0);

	cmd_path = get_path(argv[0]);
	if (!cmd_path)
	{
		print_not_found(st, argv[0]);
		return (127);
	}

	pid = fork();
	if (pid == -1)
	{
		perror(st->prog);
		free(cmd_path);
		return (127);
	}

	if (pid == 0)
	{
		execve(cmd_path, argv, environ);
		print_not_found(st, argv[0]);
		_exit(127);
	}

	if (waitpid(pid, &status, 0) == -1)
	{
		perror(st->prog);
		st->status = 127;
	}
	else
		handle_child_exit(st, status);

	free(cmd_path);
	return (0);
}

/**
 * read_line - read a line from stdin
 * @st: shell state
 *
 * Return: line read or NULL
 */
char *read_line(shell_state_t *st)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;

	print_prompt(st->interactive);
	nread = getline(&line, &len, stdin);
	if (nread == -1)
	{
		free(line);
		return (NULL);
	}

	st->line_num++;
	return (line);
}

/**
 * run_shell - main shell loop
 * @st: shell state
 *
 * Return: 0 on EOF
 */
int run_shell(shell_state_t *st)
{
	char *line;
	char **argv;

	while (1)
	{
		line = read_line(st);
		if (!line)
			return (0);

		argv = split_line(line);
		free(line);

		if (!argv)
			continue;

		if (argv[0])
			execute_cmd(st, argv);

		free_argv(argv);
	}
}
