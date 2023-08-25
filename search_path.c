#include "shell.h"

int check_file(char *full_path);

/**
 * find_program - Locates a program in the system's path.
 * @data: A pointer to the program's data.
 * Return: 0 if successful, an error code otherwise.
 */

int find_program(shell_data *data)
{
	int i = 0, ret_code = 0;
	char **directories;

	if (!data->cmd_name)
		return (2);

	if (data->cmd_name[0] == '/' || data->cmd_name[0] == '.')
		return (check_file(data->cmd_name));

	free(data->tokens[0]);
	data->tokens[0] = str_concat(dup_str("/"), data->cmd_name);
	if (!data->tokens[0])
		return (2);

	directories = tokenize_path(data);

	if (!directories || !directories[0])
	{
		errno = 127;
		return (127);
	}
	for (i = 0; directories[i]; i++)
	{
		directories[i] = str_concat(directories[i], data->tokens[0]);
		ret_code = check_file(directories[i]);
		if (ret_code == 0 || ret_code == 126)
		{
			errno = 0;
			free(data->tokens[0]);
			data->tokens[0] = dup_str(directories[i]);
			free_array_of_pointers(directories);
			return (ret_code);
		}
	}
	free(data->tokens[0]);
	data->tokens[0] = NULL;
	free_array_of_pointers(directories);
	return (ret_code);
}

/**
 * tokenize_path - Splits the path into individual directories.
 * @data: A pointer to the program's data.
 * Return: Array of path directories.
 */

char **tokenize_path(shell_data *data)
{
	int i = 0;
	int counter_directories = 2;
	char **tokens = NULL;
	char *PATH;

	PATH = env_get_key("PATH", data);
	if ((PATH == NULL) || PATH[0] == '\0')
	{
		return (NULL);
	}

	PATH = dup_str(PATH);

	for (i = 0; PATH[i]; i++)
	{
		if (PATH[i] == ':')
			counter_directories++;
	}

	tokens = malloc(sizeof(char *) * counter_directories);

	i = 0;
	tokens[i] = dup_str(_strtok(PATH, ":"));
	while (tokens[i++])
	{
		tokens[i] = dup_str(_strtok(NULL, ":"));
	}

	free(PATH);
	PATH = NULL;
	return (tokens);

}

/**
 * check_file - Checks if a file exists, is not a directory,
 * and has execution permissions.
 * @full_path: Pointer to the full file name.
 * Return: 0 on success, or an error code
 * if the file doesn't meet the conditions.
 */

int check_file(char *full_path)
{
	struct stat sb;

	if (stat(full_path, &sb) != -1)
	{
		if (S_ISDIR(sb.st_mode) ||  access(full_path, X_OK))
		{
			errno = 126;
			return (126);
		}
		return (0);
	}

	errno = 127;
	return (127);
}
