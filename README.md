# 🐚 Minishell

Minishell is a minimalistic shell inspired by Bash, written in C. It aims to replicate the core behaviors of a typical UNIX shell while maintaining a simple and educational codebase. By closely testing Bash cases, Minishell emulates standard shell behavior for pipes, redirections, environment variables, signals, and built-in commands—giving you a familiar environment for command execution.

--------------------------------------------------------------------------------

## 📖 Table of Contents
1. [Introduction](#introduction)  
2. [Features](#features)  
3. [Requirements](#requirements)  
4. [Installation](#installation)  
5. [Usage](#usage)  
6. [Built-in Commands](#built-in-commands)  
7. [Project Structure](#project-structure)  
8. [Implementation Details](#implementation-details)  
9. [Testing and Bash Compatibility](#testing-and-bash-compatibility)  
10. [Contributing](#contributing)  
11. [License](#license)  

--------------------------------------------------------------------------------

## 🔰 Introduction
Minishell is a project that implements a basic UNIX shell, adhering to constraints such as minimal global variables, strict memory management (no leaks), and correct signal handling. Think of it as a stripped-down Bash that still preserves essential interaction patterns.

--------------------------------------------------------------------------------

## ✨ Features
- Command Execution  
  • Searches for executables in your PATH or via absolute/relative paths.  
- Redirections  
  • Input redirection (<)  
  • Output redirection (>)  
  • Append redirection (>>)  
  • Here-document (<<) until a specified delimiter  
- Pipes  
  • Handles an arbitrary sequence of piped commands (cmd1 | cmd2 | …)  
- Environment Variable Expansion  
  • Allows variable references ($VAR) to expand to their set values  
  • Expands $? to the exit status of the last executed command  
- Built-in Commands  
  • Includes cd, echo, pwd, export, unset, env, and exit  
- Signal Handling  
  • Gracefully handles Ctrl-C (SIGINT), Ctrl-\ (SIGQUIT), and Ctrl-D (EOF) in interactive mode.  
- Quoting  
  • Single quotes (') disable all special interpretation within the quoted text  
  • Double quotes (") only allow expansion of $VARIABLES

--------------------------------------------------------------------------------

## 📝 Requirements
1. C Compiler (e.g., gcc)  
2. Make (to build the project)  
3. You may optionally use Docker if you wish to run in a containerized environment  

• Memory leaks are not tolerated (except for known leaks inside readline).  

--------------------------------------------------------------------------------

## 🚀 Installation

1. Clone the repository:
   ┌─(user@machine)───────────────────────────(~/path)  
   └───$ git clone https://github.com/abizyane/Minishell.git  
   └───$ cd Minishell

2. Build the project:
   ┌─(user@machine)───────────────────────────(~/Minishell)  
   └───$ make

3. Run Minishell:
   ┌─(user@machine)───────────────────────────(~/Minishell)  
   └───$ ./minishell

### 🐳 Docker (Optional)
You can spin up a container running Minishell:
  
   make up

Use make down to stop and remove the container.

--------------------------------------------------------------------------------

## 💻 Usage

Once you have launched Minishell (./minishell), you can use it like a regular shell:

• Example commands:
  echo "Hello Minishell!"  
  ls -l  
  pwd  
  cd /some/folder  
  cat file.txt | grep pattern  
  export MYVAR="Hello"  
  $MYVAR  
  exit

• Signals in Interactive Mode:
  • Ctrl-C: Prints a new prompt on a new line without exiting.  
  • Ctrl-D: Exits the shell.  
  • Ctrl-\ (SIGQUIT): Does nothing (silenced) in interactive mode.

• Redirection & Pipes Examples:
  • echo "Hello" > out.txt  
  • cat < in.txt | sort | grep pattern >> results.txt  
  • cat << EOF  
    [Your input here]  
    EOF

--------------------------------------------------------------------------------

## 🔧 Built-in Commands

| Command    | Description                                                     |
|------------|-----------------------------------------------------------------|
| cd         | Changes the current directory (relative or absolute paths).     |
| echo [-n]  | Prints arguments to stdout; -n omits the trailing newline.      |
| pwd        | Prints the current working directory.                           |
| env        | Displays the current environment variables.                     |
| export     | Sets/updates environment variables.                             |
| unset      | Unsets/removes environment variables.                           |
| exit       | Exits the shell.                                               |

--------------------------------------------------------------------------------

## 📂 Project Structure
Minishell source files are logically separated into different directories:

Minishell/  
├── Dockerfile              # Docker configuration  
├── LICENSE                 # MIT License  
├── Makefile                # Build configuration  
├── minishell.c             # Main entry point  
├── minishell.h             # Common header  
├── Libft/                  # Custom utility library  
│   ├── Makefile  
│   ├── ft_*.c  
│   └── libft.h  
├── builtins/               # Built-in commands (cd, echo, etc.)  
├── exec/                   # Command execution, env handling, redirections, signals  
└── parser/                 # Tokenizing, parsing, and expansions  

--------------------------------------------------------------------------------

## 🧪 Testing and Bash Compatibility
Minishell has been tested against many Bash use cases to ensure consistent behavior:
• Complex piping, redirection chaining, and here-doc scenarios.  
• Edge cases with environment variables (unset, export without values, etc.).  
• Signal handling interactions (Ctrl-C, Ctrl-D, and Ctrl-\).  

If you are uncertain about a behavior, we recommend comparing the output in Bash. Minishell strives to match Bash’s defaults as closely as possible within the project’s requirements.

--------------------------------------------------------------------------------

## 📜 License
This project is licensed under the MIT License. See [LICENSE](LICENSE) for details.
