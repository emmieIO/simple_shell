#include "shell.h"

/**
 * free_recurrent_data - Frees the fields needed for each loop iteration.
 * @data: A structure containing program-specific data.
 * Return: Nothing.
 */

void free_recurrent_data(shell_data *data)
{
	if (data->tokens)
		free_array_of_pointers(data->tokens);
	if (data->lineptr)
		free(data->lineptr);
	if (data->cmd_name)
		free(data->cmd_name);

	data->lineptr = NULL;
	data->cmd_name = NULL;
	data->tokens = NULL;
}

/**
 * free_all_data - Frees all fields within the data structure.
 * @data: A structure containing program-specific data.
 * Return: Nothing.
 */

void free_all_data(shell_data *data)
{
	if (data->fd != 0)
	{
		if (close(data->fd))
			perror(data->myprogram);
	}
	free_recurrent_data(data);
	free_array_of_pointers(data->env);
	free_array_of_pointers(data->aliases);
}

/**
 * free_array_of_pointers - Frees each pointer in an array
 * of pointers and the array itself.
 * @array: Array of pointers.
 * Return: Nothing.
 */

void free_array_of_pointers(char **array)
{
	int i;

	if (array != NULL)
	{
		for (i = 0; array[i]; i++)
			free(array[i]);

		free(array);
		array = NULL;
	}
}
