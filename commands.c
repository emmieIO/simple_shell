#include "shell.h"

/**
 * builtins_list - search for match and execute the associate builtin
 * @data: struct for the program's data
 * Return: Returns the return of the function executed is there is a match,
 * otherwise returns -1.
 **/
int builtins_list(shell_data *data)
{
	int counter;
	builtins options[] = {
		{"exit", builtin_exit},
		{"help", builtin_help},
		{"cd", builtin_cd},
		{"alias", builtin_alias},
		{"env", builtin_env},
		{"setenv", builtin_set_env},
		{"unsetenv", builtin_unset_env},
		{NULL, NULL}
	};

	for (counter = 0; options[counter].builtin != NULL; counter++)
	{
		if (str_compare(options[counter].builtin, data->cmd_name, 0))
		{

			return (options[counter].function(data));
		}

	}
	return (-1);
}
