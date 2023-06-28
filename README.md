# Minishell: Custon Shell Implementation 

This project involves creating a custom shell in C. The shell displays a prompt when waiting for a new command, maintains a history of commands, and searches and launches the right executable based on the PATH variable or using a relative or an absolute path.

## Getting Started
These instructions will get you a copy of the project up and running on your local machine for development and testing purposes.

## Prerequisites
C Compiler<br>
Installation<br>
Clone the repository to your local machine.<br>
Navigate to the project directory.<br>
Compile the project using your C compiler.<br>
Project Structure<br>

## Features:
Displays a prompt when waiting for a new command.<br>
Maintains a working history of commands.<br>
Searches and launches the right executable (based on the PATH variable or using a relative or an absolute path).<br>
Handles single and double quotes.<br>
Implements redirections (<, >, <<, >>).<br>
Implements pipes (|).<br>
Handles environment variables ($ followed by a sequence of characters).<br>
Handles $? which expands to the exit status of the most recently executed foreground pipeline.<br>
Handles ctrl-C, ctrl-D and ctrl-\ which behave like in bash.<br>
Implements the following builtins: echo with option -n, cd with only a relative or absolute path, pwd with no options, export with no options, unset with no options, env with no options or arguments, exit with no options.<br>
