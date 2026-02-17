#include "shell.h"

/**
 * main - entry point for simple shell (0.1)
 * @ac: argument count (unused)
 * @av: argument vector
 *
 * Return: 0 on success
 */
int main(int ac, char **av)
{
	shell_state_t st;
	char *line = NULL, *cmd = NULL;
	size_t len = 0;
	ssize_t nread;
	pid_t pid;
	int status;
	char *argv_exec[2];

	(void)ac;
	st.prog = av[0];
	st.line_num = 0;
	st.interactive = isatty(STDIN_FILENO);

	while (1)
	{
		print_prompt(st.interactive);

		nread = getline(&line, &len, stdin);
		if (nread == -1)
		{
			free(line);
			return (0);
		}

		st.line_num++;

		cmd = strtok(line, " \t\n");
		if (cmd == NULL)
			continue;

		if (access(cmd, X_OK) == -1)
		{
			print_not_found(&st, cmd);
			continue;
		}

		pid = fork();
		if (pid == -1)
		{
			perror(st.prog);
			continue;
		}

		if (pid == 0)
		{
			argv_exec[0] = cmd;
			argv_exec[1] = NULL;

			execve(cmd, argv_exec, environ);
			perror(st.prog);
			_exit(127);
		}

		waitpid(pid, &status, 0);
	}
}
