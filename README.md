# Minishell: Custon Shell Implementation 

This project involves creating a custom shell in C. The shell displays a prompt when waiting for a new command, maintains a history of commands, and searches and launches the right executable based on the PATH variable or using a relative or an absolute path.

## Getting Started
These instructions will get you a copy of the project up and running on your local machine for development and testing purposes.

## Prerequisites
C Compiler
Installation
Clone the repository to your local machine.
Navigate to the project directory.
Compile the project using your C compiler.
Project Structure

## Features:
Displays a prompt when waiting for a new command.
Maintains a working history of commands.
Searches and launches the right executable (based on the PATH variable or using a relative or an absolute path).
Handles single and double quotes.
Implements redirections (<, >, <<, >>).
Implements pipes (|).
Handles environment variables ($ followed by a sequence of characters).
Handles $? which expands to the exit status of the most recently executed foreground pipeline.
Handles ctrl-C, ctrl-D and ctrl-\ which behave like in bash.
Implements the following builtins: echo with option -n, cd with only a relative or absolute path, pwd with no options, export with no options, unset with no options, env with no options or arguments, exit with no options.
