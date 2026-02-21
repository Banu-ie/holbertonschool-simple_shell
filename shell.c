#include "shell.h"

/**
 * handle_child_exit - handle child process exit status
 * @st: shell state
 * @status: waitpid status
 */
static void handle_child_exit(shell_state_t *st, int status)
{
	if (WIFEXITED(status))
		st->status = WEXITSTATUS(status);
	else
		st->status = 127; /* abnormal exit */
}

/**
 * execute_cmd - forks and executes a command
 * @st: shell state
 * @argv: argument vector
 *
 * Return: 0 always
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
		st->status = 127; /* command not found */
		return (127);
	}

	pid = fork();
	if (pid == -1)
	{
		perror(st->prog);
		free(cmd_path);
		st->status = 127; /* fork failed */
		return (127);
	}

	if (pid == 0)
	{
		execve(cmd_path, argv, NULL); /* inherit environment */
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
static char *read_line(shell_state_t *st)
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
 * process_line - read and execute one line
 * @st: shell state
 *
 * Return: 1 if should continue, 0 on EOF
 */
static int process_line(shell_state_t *st)
{
	char *line = read_line(st);
	char **argv;

	if (!line)
		return (0);

	argv = tokenize_line(line);
	free(line);

	if (!argv)
		return (1);

	if (argv[0])
		execute_cmd(st, argv);

	free_argv(argv);
	return (1);
}

/**
 * run_shell - main shell loop
 * @st: shell state
 *
 * Return: 0 on EOF
 */
int run_shell(shell_state_t *st)
{
	while (process_line(st))
		;

	return (0);
}
