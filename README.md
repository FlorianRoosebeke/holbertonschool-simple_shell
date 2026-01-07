# Simple Shell

A simple UNIX command line interpreter (shell) built in C as part of the Holberton School curriculum.

## Description

This project is a minimalist implementation of a shell that reads commands from standard input and executes them. It replicates basic functionality of shells like `sh`, including command execution, built-in commands, and PATH resolution.

## Features

- Display a prompt and wait for user input
- Execute commands from PATH or by absolute/relative path
- Built-in commands: `exit` and `env`
- Signal handling (Ctrl+C displays a new prompt instead of exiting)
- Works in both interactive and non-interactive mode
- Error handling with appropriate messages

## Compilation

Compile the shell with the following command:

```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
```

## Usage

### Interactive Mode

Run the shell:
```bash
./hsh
```

Then enter commands at the prompt:
```bash
$ ls
file1 file2 file3
$ pwd
/home/user/holbertonschool-simple_shell
$ /bin/echo "Hello World"
Hello World
$ exit
```

### Non-Interactive Mode

You can also pipe commands into the shell:
```bash
$ echo "ls -l" | ./hsh
total 40
-rw-r--r-- 1 user user 1234 Jan 7 10:00 file1
```

## Built-in Commands

- **exit** - Exit the shell
- **env** - Print the environment variables

## File Structure

- `main.c` - Entry point of the shell, main loop
- `main.h` - Header file with function prototypes and includes
- `display_prompt.c` - Displays the shell prompt
- `read_line.c` - Reads user input from stdin
- `clean_line.c` - Cleans and validates the input line
- `execute_command.c` - Handles command execution and PATH resolution
- `get_token.c` - Tokenizes command line input
- `get_path.c` - Retrieves and parses the PATH environment variable
- `print_env.c` - Implements the env built-in command
- `handle_sigint.c` - Handles SIGINT signal (Ctrl+C)
- `man/man_1_simple_shell.1` - Manual page for the shell

## How It Works

1. The shell displays a prompt (`$ `)
2. Waits for user input
3. Parses the input into tokens (command and arguments)
4. Checks if it's a built-in command
5. If not, searches for the command:
   - If the command contains `/`, treats it as a path
   - Otherwise, searches in PATH directories
6. Executes the command using `fork()` and `execve()`
7. Returns to step 1

'''mermaid
flowchart TD
    Start([START]) --> Loop((LOOP INFINI))

    Loop --> Prompt[Affiche '$']
    Prompt --> Read[Lit commande]
    Read --> EOF{EOF?}

    EOF -->|Oui| End([FIN])
    EOF -->|Non| Check{Commande vide?}

    Check -->|Oui| Loop
    Check -->|Non| Exit{exit?}

    Exit -->|Oui| End
    Exit -->|Non| Env{env?}

    Env -->|Oui| Print[Affiche variables]
    Print --> Loop

    Env -->|Non| Path{Avec / ?}

    Path -->|Oui| Abs[Chemin absolu]
    Path -->|Non| Search[Cherche dans PATH]

    Abs --> Exec[fork + execve]
    Search --> Found{Trouvé?}

    Found -->|Oui| Exec
    Found -->|Non| Error[Erreur: not found]

    Exec --> Loop
    Error --> Loop

    style Start fill:#90EE90
    style End fill:#FFB6C1
    style Loop fill:#87CEEB
    style Exec fill:#FFD700
    style Error fill:#FF6B6B
'''

## Examples

```bash
$ ./hsh
$ ls -la
total 100
drwxr-xr-x 3 user user  4096 Jan  7 10:00 .
drwxr-xr-x 5 user user  4096 Jan  7 09:00 ..
-rw-r--r-- 1 user user   242 Jan  7 10:00 clean_line.c
$ pwd
/home/user/holbertonschool-simple_shell
$ env
PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin
HOME=/home/user
...
$ exit
$
```

## Authors

Tom Vieilledent
Florian Roosebeke

## Man Page

To view the manual page:
```bash
man ./man/man_1_simple_shell.1
```

Or install it system-wide:
```bash
sudo cp man/man_1_simple_shell.1 /usr/share/man/man1/hsh.1
man hsh
```
