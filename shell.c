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
        return 0;

    cmd_path = get_path(argv[0]);
    if (!cmd_path)
    {
        print_not_found(st, argv[0]);
        st->status = 127;  /* command not found */
        return (127);
    }

    pid = fork();
    if (pid == -1)
    {
        perror(st->prog);
        free(cmd_path);
        st->status = 127;  /* fork failed */
        return 0;
    }

    if (pid == 0)
    {
        execve(cmd_path, argv, environ);
        print_not_found(st, argv[0]); /* execve failed */
        _exit(127);
    }

    if (waitpid(pid, &status, 0) == -1)
    {
        perror(st->prog);
        st->status = 127; /* waitpid failed */
    }
    else
    {
        if (WIFEXITED(status))
            st->status = WEXITSTATUS(status); /* child exit code */
        else
            st->status = 127; /* abnormal exit */
    }

    free(cmd_path);
    return 0;
}

/**
 * run_shell - main shell loop
 * @st: shell state
 *
 * Return: 0 on EOF
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
