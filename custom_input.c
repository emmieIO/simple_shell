#include "shell.h"

/**
* _readInput - Takes input from the user.
* @data: struct for the program's data
*
* Return: returns size of bytes read.
*/
int _readInput(shell_data *data)
{
	char buff[BUFFER_SIZE] = {'\0'};
	static char *arr_cmd[10] = {NULL};
	static char arr_ops[10] = {'\0'};
	ssize_t chars_read, i = 0;


	if (!arr_cmd[0] || (arr_ops[0] == '&' && errno != 0) ||
		(arr_ops[0] == '|' && errno == 0))
	{
		for (i = 0; arr_cmd[i]; i++)
		{
			free(arr_cmd[i]);
			arr_cmd[i] = NULL;
		}

		chars_read = read(data->fd, &buff, BUFFER_SIZE - 1);
		if (chars_read == 0)
			return (-1);

		i = 0;
		do {
			arr_cmd[i] = dup_str(_strtok(i ? NULL : buff, "\n;"));
			i = ops_handle(arr_cmd, i, arr_ops);
		} while (arr_cmd[i++]);
	}

	data->lineptr = arr_cmd[0];
	for (i = 0; arr_cmd[i]; i++)
	{
		arr_cmd[i] = arr_cmd[i + 1];
		arr_ops[i] = arr_ops[i + 1];
	}

	return (str_length(data->lineptr));
}


/**
* ops_handle - Examines and separates commands
* based on the && and || operators.
*
* This function examines an array of commands
* and separates them based on the && and || operators.
* It takes the current command index, along with arrays
* of commands and logical operators, to determine the
* execution order.
*
* @arr_cmd: An array containing the commands to be processed.
* @i: The index pointing to the current command in the array.
* @arr_ops: An array holding the logical operators corresponding
* to previous commands.
*
* Return: The index of the last processed command within
* the array_commands.
*/

int ops_handle(char *arr_cmd[], int i, char arr_ops[])
{
	char *tmp = NULL;
	int j;

	for (j = 0; arr_cmd[i] != NULL  && arr_cmd[i][j]; j++)
	{
		if (arr_cmd[i][j] == '&' && arr_cmd[i][j + 1] == '&')
		{
			tmp = arr_cmd[i];
			arr_cmd[i][j] = '\0';
			arr_cmd[i] = dup_str(arr_cmd[i]);
			arr_cmd[i + 1] = dup_str(tmp + j + 2);
			i++;
			arr_ops[i] = '&';
			free(tmp);
			j = 0;
		}
		if (arr_cmd[i][j] == '|' && arr_cmd[i][j + 1] == '|')
		{
			tmp = arr_cmd[i];
			arr_cmd[i][j] = '\0';
			arr_cmd[i] = dup_str(arr_cmd[i]);
			arr_cmd[i + 1] = dup_str(tmp + j + 2);
			i++;
			arr_ops[i] = '|';
			free(tmp);
			j = 0;
		}
	}
	return (i);
}
