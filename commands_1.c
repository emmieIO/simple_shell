#include "shell.h"

/**
 * builtin_exit - Exits the program with a status code.
 * @data: A struct containing program data.
 * Return: Always 0 for success, or a different number if specified.
 */

int builtin_exit(shell_data *data)
{
	int i;

	if (data->tokens[1] != NULL)
	{/*if exists arg for exit, check if is a number*/
		for (i = 0; data->tokens[1][i]; i++)
			if ((data->tokens[1][i] < '0' || data->tokens[1][i] > '9')
				&& data->tokens[1][i] != '+')
			{/*if is not a number*/
				errno = 2;
				return (2);
			}
		errno = _atoi(data->tokens[1]);
	}
	free_all_data(data);
	exit(errno);
}

/**
 * builtin_cd - Change the current directory.
 * @data: A struct containing program data.
 * Return: Always 0 for success, or a different number if specified.
 */

int builtin_cd(shell_data *data)
{
	char *dir_home = env_get_key("HOME", data), *dir_old = NULL;
	char old_dir[128] = {0};
	int error_code = 0;

	if (data->tokens[1])
	{
		if (str_compare(data->tokens[1], "-", 0))
		{
			dir_old = env_get_key("OLDPWD", data);
			if (dir_old)
				error_code = set_work_directory(data, dir_old);
			_print(env_get_key("PWD", data));
			_print("\n");

			return (error_code);
		}
		else
		{
			return (set_work_directory(data, data->tokens[1]));
		}
	}
	else
	{
		if (!dir_home)
			dir_home = getcwd(old_dir, 128);

		return (set_work_directory(data, dir_home));
	}
	return (0);
}

/**
 * set_work_directory - Sets the working directory.
 * @data: A struct containing program data.
 * @new_dir: Path to be set as the working directory.
 * Return: Always 0 for success, or a different number if specified.
 */

int set_work_directory(shell_data *data, char *new_dir)
{
	char old_dir[128] = {0};
	int err_code = 0;

	getcwd(old_dir, 128);

	if (!str_compare(old_dir, new_dir, 0))
	{
		err_code = chdir(new_dir);
		if (err_code == -1)
		{
			errno = 2;
			return (3);
		}
		env_set_key("PWD", new_dir, data);
	}
	env_set_key("OLDPWD", old_dir, data);
	return (0);
}

/**
 * builtin_help - Displays the runtime environment of the shell.
 * @data: A structure containing program-specific data.
 * Return: Always 0 upon success, or another value if specified by arguments.
 */

int builtin_help(shell_data *data)
{
	int i, length = 0;
	char *msgs[6] = {NULL};

	msgs[0] = HELP_MSG;

	/* validate args */
	if (data->tokens[1] == NULL)
	{
		_print(msgs[0] + 6);
		return (1);
	}
	if (data->tokens[2] != NULL)
	{
		errno = E2BIG;
		perror(data->cmd_name);
		return (5);
	}
	msgs[1] = HELP_EXIT_MSG;
	msgs[2] = HELP_ENV_MSG;
	msgs[3] = HELP_SETENV_MSG;
	msgs[4] = HELP_UNSETENV_MSG;
	msgs[5] = HELP_CD_MSG;

	for (i = 0; msgs[i]; i++)
	{

		length = str_length(data->tokens[1]);
		if (str_compare(data->tokens[1], msgs[i], length))
		{
			_print(msgs[i] + length + 1);
			return (1);
		}
	}
	/*if there is no match, print error and return -1 */
	errno = EINVAL;
	perror(data->cmd_name);
	return (0);
}

/**
 * builtin_alias - Manages aliases, allowing addition, removal, and display.
 * @data: A structure holding program-specific data.
 * Return: 0 on success, or a different value if specified by arguments.
 */

int builtin_alias(shell_data *data)
{
	int i = 0;

	/* if there are no arguments, print all environment */
	if (data->tokens[1] == NULL)
		return (print_alias(data, NULL));

	while (data->tokens[++i])
	{/* if there are arguments, set or print each env variable*/
		if (count_characters(data->tokens[i], "="))
			set_alias(data->tokens[i], data);
		else
			print_alias(data, data->tokens[i]);
	}

	return (0);
}
