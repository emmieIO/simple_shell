#include "shell.h"

/**
 * _print - Writes an array of characters to the standard output.
 * @string: Pointer to the array of characters.
 * Return: The number of bytes written.
 * On error, -1 is returned, and errno is set appropriately.
 */

int _print(char *string)
{
	return (write(STDOUT_FILENO, string, str_length(string)));
}

/**
 * _printe - Writes an array of characters to the standard error.
 * @string: Pointer to the array of characters.
 * Return: The number of bytes written. On error,
 * -1 is returned, and errno is set appropriately.
 */

int _printe(char *string)
{
	return (write(STDERR_FILENO, string, str_length(string)));
}

/**
 * _print_error - Writes an array of characters to the standard error.
 * @data: A pointer to the program's data.
 * @errorcode: Error code to print.
 * Return: The number of bytes written.
 * On error, -1 is returned, and errno is set appropriately.
 */

int _print_error(int errorcode, shell_data *data)
{
	char n_as_string[10] = {'\0'};

	long_to_string((long) data->execution_count, n_as_string, 10);

	if (errorcode == 2 || errorcode == 3)
	{
		_printe(data->myprogram);
		_printe(": ");
		_printe(n_as_string);
		_printe(": ");
		_printe(data->tokens[0]);
		if (errorcode == 2)
			_printe(": Illegal number: ");
		else
			_printe(": can't cd to ");
		_printe(data->tokens[1]);
		_printe("\n");
	}
	else if (errorcode == 127)
	{
		_printe(data->myprogram);
		_printe(": ");
		_printe(n_as_string);
		_printe(": ");
		_printe(data->cmd_name);
		_printe(": not found\n");
	}
	else if (errorcode == 126)
	{
		_printe(data->myprogram);
		_printe(": ");
		_printe(n_as_string);
		_printe(": ");
		_printe(data->cmd_name);
		_printe(": Permission denied\n");
	}
	return (0);
}
