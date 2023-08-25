#include "shell.h"

/**
 * env_get_key - Retrieves the value of an environment variable.
 * @key: The environment variable to look for.
 * @data: A structure containing program-specific data.
 * Return: A pointer to the value of the variable, or NULL if it doesn't exist.
 */

char *env_get_key(char *key, shell_data *data)
{
	int i, key_length = 0;

	if (key == NULL || data->env == NULL)
		return (NULL);

	key_length = str_length(key);

	for (i = 0; data->env[i]; i++)
	{
		if (str_compare(key, data->env[i], key_length) &&
		 data->env[i][key_length] == '=')
		{
			return (data->env[i] + key_length + 1);
		}
	}

	return (NULL);
}

/**
 * env_set_key - Overwrites or creates an
 * environment variable with a new value.
 * @key: Name of the variable to set.
 * @value: New value for the variable.
 * @data: A structure containing program-specific data.
 * Return: 1 if parameters are NULL, 2 on error, or 0 on success.
 */

int env_set_key(char *key, char *value, shell_data *data)
{
	int i, key_length = 0, is_new_key = 1;

	if (key == NULL || value == NULL || data->env == NULL)
		return (1);

	key_length = str_length(key);

	for (i = 0; data->env[i]; i++)
	{
		if (str_compare(key, data->env[i], key_length) &&
		 data->env[i][key_length] == '=')
		{
			is_new_key = 0;
			free(data->env[i]);
			break;
		}
	}

	data->env[i] = str_concat(dup_str(key), "=");
	data->env[i] = str_concat(data->env[i], value);

	if (is_new_key)
	{
		data->env[i + 1] = NULL;
	}
	return (0);
}

/**
 * env_remove_key - Removes a key from the environment.
 * @key: The key to be removed.
 * @data: A structure containing program-specific data.
 * Return: 1 if the key was removed, 0 if the key does not exist.
 */

int env_remove_key(char *key, shell_data *data)
{
	int i, key_length = 0;

	if (key == NULL || data->env == NULL)
		return (0);

	key_length = str_length(key);

	for (i = 0; data->env[i]; i++)
	{
		if (str_compare(key, data->env[i], key_length) &&
		 data->env[i][key_length] == '=')
		{
			free(data->env[i]);

			i++;
			for (; data->env[i]; i++)
			{
				data->env[i - 1] = data->env[i];
			}

			data->env[i - 1] = NULL;
			return (1);
		}
	}
	return (0);
}


/**
 * print_environ - Prints the current environment.
 * @data: A structure containing program-specific data.
 * Return: Nothing.
 */

void print_environ(shell_data *data)
{
	int j;

	for (j = 0; data->env[j]; j++)
	{
		_print(data->env[j]);
		_print("\n");
	}
}
