#include "shell.h"

extern char **environ;

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
        st->status = 127;
        return (0);
    }

    pid = fork();
    if (pid == -1)
    {
        perror(st->prog);
        free(cmd_path);
        st->status = 127;
        return (0);
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
    {
        if (WIFEXITED(status))
            st->status = WEXITSTATUS(status);
        else
            st->status = 127;
    }

    free(cmd_path);
    return (0);
}

/**
 * run_shell - main shell loop
 * @st: shell state
 *
 * Return: last status on EOF
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
            return (st->status);
        }

        st->line_num++;

        argv = tokenize_line(line);
        if (!argv)
            continue;

        /* ===== BUILTIN EXIT (TASK 5) ===== */
        if (argv[0] && strcmp(argv[0], "exit") == 0)
        {
            free_argv(argv);
            free(line);
            exit(st->status);
        }
        /* ================================= */

        if (argv[0])
            execute_cmd(st, argv);

        free_argv(argv);
    }
}
