#include "shell.h"

/**
 * print_alias - Handles adding, removing, or displaying aliases.
 * @data: A structure containing program-specific data.
 * @alias: The name of the alias to be printed.
 * Return: 0 on success, or a different value if specified by arguments.
 */

int print_alias(shell_data *data, char *alias)
{
	int i, j, alias_length;
	char buffer[250] = {'\0'};

	if (data->aliases)
	{
		alias_length = str_length(alias);
		for (i = 0; data->aliases[i]; i++)
		{
			if (!alias || (str_compare(data->aliases[i], alias, alias_length)
				&&	data->aliases[i][alias_length] == '='))
			{
				for (j = 0; data->aliases[i][j]; j++)
				{
					buffer[j] = data->aliases[i][j];
					if (data->aliases[i][j] == '=')
						break;
				}
				buffer[j + 1] = '\0';
				buffer_add(buffer, "'");
				buffer_add(buffer, data->aliases[i] + j + 1);
				buffer_add(buffer, "'\n");
				_print(buffer);
			}
		}
	}

	return (0);
}

/**
 * get_alias - Handles adding, removing, or displaying aliases.
 * @data: A structure containing program-specific data.
 * @name: The name of the requested alias.
 * Return: 0 on success, or a different value if specified by arguments.
 */

char *get_alias(shell_data *data, char *name)
{
	int i, alias_length;

	if (name == NULL || data->aliases == NULL)
		return (NULL);

	alias_length = str_length(name);

	for (i = 0; data->aliases[i]; i++)
	{
		if (str_compare(name, data->aliases[i], alias_length) &&
			data->aliases[i][alias_length] == '=')
		{
			return (data->aliases[i] + alias_length + 1);
		}
	}

	return (NULL);

}

/**
 * set_alias - Adds or overrides an alias.
 * @alias_string: The alias to be set in the form (name='value').
 * @data: A structure containing program-specific data.
 * Return: 0 on success, or a different value if specified by arguments.
 */

int set_alias(char *alias_string, shell_data *data)
{
	int i, j;
	char buffer[250] = {'0'}, *temp = NULL;


	if (alias_string == NULL ||  data->aliases == NULL)
		return (1);

	for (i = 0; alias_string[i]; i++)
		if (alias_string[i] != '=')
			buffer[i] = alias_string[i];
		else
		{
			temp = get_alias(data, alias_string + i + 1);
			break;
		}

	for (j = 0; data->aliases[j]; j++)
		if (str_compare(buffer, data->aliases[j], i) &&
			data->aliases[j][i] == '=')
		{
			free(data->aliases[j]);
			break;
		}

	if (temp)
	{
		buffer_add(buffer, "=");
		buffer_add(buffer, temp);
		data->aliases[j] = dup_str(buffer);
	}
	else
		data->aliases[j] = dup_str(alias_string);
	return (0);
}
