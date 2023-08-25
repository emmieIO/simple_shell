#include "shell.h"

/**
 * main - Initializes program variables.
 * @argc: Number of command-line arguments.
 * @argv: Array of command-line argument values.
 * @env: Array of environment variables.
 * Return: 0 on success.
 */

int main(int argc, char *argv[], char *env[])
{
	shell_data data_struct = {NULL}, *data = &data_struct;
	char *prompt = "";

	init_data(data, argc, argv, env);

	signal(SIGINT, _ctrl_c);

	if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO) && argc == 1)
	{
		errno = 2;
		prompt = PROMPT_MSG;
	}
	errno = 0;
	itrator(prompt, data);
	return (0);
}

/**
 * _ctrl_c - Prints the prompt on a new line when the program
 * receives the SIGINT (ctrl + c) signal.
 * @UNUSED: Option of the prototype (not used in the function).
 */

void _ctrl_c(int opr UNUSED)
{
	_print("\n");
	_print(PROMPT_MSG);
}

/**
 * init_data - Initializes a data structure with program information.
 * @data: Pointer to the data structure.
 * @argv: Array of arguments passed during program execution.
 * @env: Environment variables passed to the program.
 * @argc: Number of values received from the command line.
 */

void init_data(shell_data *data, int argc, char *argv[], char **env)
{
	int counter = 0;

	data->myprogram = argv[0];
	data->lineptr = NULL;
	data->cmd_name = NULL;
	data->execution_count = 0;

	if (argc == 1)
		data->fd = STDIN_FILENO;
	else
	{
		data->fd = open(argv[1], O_RDONLY);
		if (data->fd == -1)
		{
			_printe(data->myprogram);
			_printe(": 0: Can't open ");
			_printe(argv[1]);
			_printe("\n");
			exit(127);
		}
	}
	data->tokens = NULL;
	data->env = malloc(sizeof(char *) * 50);
	if (env)
	{
		for (; env[counter]; counter++)
		{
			data->env[counter] = dup_str(env[counter]);
		}
	}
	data->env[counter] = NULL;
	env = data->env;

	data->aliases = malloc(sizeof(char *) * 20);
	for (counter = 0; counter < 20; counter++)
	{
		data->aliases[counter] = NULL;
	}
}

/**
 * itrator - Enters an infinite loop to display the provided prompt.
 * @prompt: The prompt to be printed.
 * @data: The structure containing program data.
 */

void itrator(char *prompt, shell_data *data)
{
	int er_c = 0, str_len = 0;

	while (++(data->execution_count))
	{
		_print(prompt);
		er_c = str_len = _readInput(data);

		if (er_c == EOF)
		{
			free_all_data(data);
			exit(errno);
		}
		if (str_len >= 1)
		{
			expand_alias(data);
			expand_variables(data);
			tokenize(data);
			if (data->tokens[0])
			{
				er_c = execute(data);
				if (er_c != 0)
					_print_error(er_c, data);
			}
			free_recurrent_data(data);
		}
	}
}
