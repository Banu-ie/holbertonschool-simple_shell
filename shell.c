#include "shell.h"

/**
 * execute_cmd - forks and executes a command with arguments
 * @st: shell state
 * @argv: NULL-terminated argument vector
 *
 * Return: 0 always
 */
int execute_cmd(shell_state_t *st, char **argv)
{
    pid_t pid;
    int status;
    char *cmd_path;

    if (!argv || !argv[0])
        return 0;

    /* Find the command path using PATH */
    cmd_path = get_path(argv[0]);
    if (!cmd_path)
    {
        print_not_found(st, argv[0]);
        return 0;
    }

    pid = fork();
    if (pid == -1)
    {
        perror(st->prog);
        free(cmd_path);
        return 0;
    }

    if (pid == 0)
    {
        /* Execute the command */
        execve(cmd_path, argv, environ);
        perror(st->prog);
        _exit(127);
    }

    /* Wait for child process */
    waitpid(pid, &status, 0);
    free(cmd_path);
    return 0;
}

/**
 * run_shell - main loop of the shell
 * @st: shell state
 *
 * Return: 0 on success
 */
int run_shell(shell_state_t *st)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;
    char **argv;

    while (1)
    {
        print_prompt(st->interactive);
        nread = getline(&line, &len, stdin);

        if (nread == -1)
        {
            free(line);
            return 0;
        }

        st->line_num++;

        argv = tokenize_line(line);
        if (!argv)
            continue;

        if (argv[0])
            execute_cmd(st, argv);

        free_argv(argv);
    }
}
