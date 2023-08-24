#include "shell.h"
/**
 * main - initialize the variables of the program
 * @argc: number of values received from the command line
 * @argv: values received from the command line
 * @env: number of values received from the command line
 * Return: zero on succes.
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
 * _ctrl_c - print the prompt in a new line
 * when the signal SIGINT (ctrl + c) is send to the program
 * @UNUSED: option of the prototype
 */
void _ctrl_c(int opr UNUSED)
{
	_print("\n");
	_print(PROMPT_MSG);
}

/**
 * init_data - initialize the struct with the info of the program
 * @data: pointer to the structure of data
 * @argv: array of arguments pased to the program execution
 * @env: environ pased to the program execution
 * @argc: number of values received from the command line
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
 * itrator - its a infinite loop that shows the prompt
 * @prompt: prompt to be printed
 * @data: its a infinite loop that shows the prompt
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
