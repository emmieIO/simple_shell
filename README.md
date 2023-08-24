## Collaborators/Authors

[Vivian](https://github.com/vivianokose) and [MARK](https://github.com/emmieIO)_

## About Project

![simple_shell](https://s3.amazonaws.com/intranet-projects-files/holbertonschool-low_level_programming/235/shell.jpeg)

# ALX Simple Shell Project

The ALX Simple Shell project is an implementation of a simple shell program that provides a command-line interface for users to interact with the operating system. The project involves the development of a basic shell with various functionalities and features.

## Project Overview

The main objective of the ALX Simple Shell project is to create a lightweight shell that allows users to execute commands, both system commands and shell built-in commands. The shell supports features such as input/output redirection, pipeline creation with multiple commands, background process execution, and signal handling.

## Project Tasks

The following are some key tasks involved in the ALX Simple Shell project:

1. **Command Execution**: Implement the functionality to execute commands entered by the user. This involves parsing and interpreting the user's input, identifying the command and its arguments, and executing the command using system calls.

2. **Shell Built-in Commands**: Implement built-in commands such as `cd`, `pwd`, `echo`, `exit`, etc. These commands should be executed directly within the shell process and not by forking a child process.

3. **Input/Output Redirection**: Implement the ability to redirect command input or output to files. This involves detecting the redirection operators (`<`, `>`, `>>`) in the user's input and handling the file descriptors appropriately.

4. **Pipeline Support**: Implement command pipelines, allowing users to chain multiple commands together using the `|` operator. Each command in the pipeline should have its own child process, and the output of one command should be piped to the input of the next command.

5. **Background Processes**: Implement the ability to run commands in the background by appending the `&` symbol to the command. The shell should not wait for the completion of background processes and should continue to accept new commands.

6. **Signal Handling**: Implement signal handling to ensure proper handling of signals such as `Ctrl+C` and `Ctrl+Z`. For example, `Ctrl+C` should send a SIGINT signal to the foreground process and not terminate the shell itself.

## Conclusion

The ALX Simple Shell project involves the development of a basic shell that provides a command-line interface for users to interact with the operating system. The project tasks include implementing command execution, shell built-in commands, input/output redirection, pipeline support, background processes, and signal handling. By completing these tasks, the project aims to create a functional and efficient shell program..
