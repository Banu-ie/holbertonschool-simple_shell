# Simple Shell (hsh)

A simple UNIX command interpreter written in C (Holberton School project).

## Compilation
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh

## Usage

Interactive mode (type commands manually):
./hsh
($) /bin/ls
($) ls -l
($) exit

Non-interactive mode (commands from pipe/file):
echo "/bin/ls" | ./hsh
cat file_with_commands | ./hsh

## Built-ins
- exit: exits the shell
- env: prints the environment

## Authors
See AUTHORS file.
