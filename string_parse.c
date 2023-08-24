#include "shell.h"
/**
 * tokenize - this function separate the string using a designed delimiter
 * @data: a pointer to the program's data
 * Return: an array of the different parts of the string
 */
void tokenize(shell_data *data)
{
	char *split = " \t";
	int i, j, counter = 2, length;

	length = str_length(data->lineptr);
	if (length)
	{
		if (data->lineptr[length - 1] == '\n')
			data->lineptr[length - 1] = '\0';
	}

	for (i = 0; data->lineptr[i]; i++)
	{
		for (j = 0; split[j]; j++)
		{
			if (data->lineptr[i] == split[j])
				counter++;
		}
	}

	data->tokens = malloc(counter * sizeof(char *));
	if (data->tokens == NULL)
	{
		perror(data->myprogram);
		exit(errno);
	}
	i = 0;
	data->tokens[i] = dup_str(_strtok(data->lineptr, split));
	data->cmd_name = dup_str(data->tokens[0]);
	while (data->tokens[i++])
	{
		data->tokens[i] = dup_str(_strtok(NULL, split));
	}
}
