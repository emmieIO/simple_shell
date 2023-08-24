#ifndef SHELL_H
#define SHELL_H

#include <stdio.h> /* for printf*/
#include <unistd.h> /* for fork, execve*/
#include <stdlib.h>
#include <string.h> /* for strtok*/
#include <stddef.h>
#include <errno.h> /* for errno and perror */
#include <sys/types.h> /* for type pid */
#include <sys/wait.h> /* for wait */
#include <sys/stat.h> /* for use of stat function */
#include <signal.h> /* for signal management */
#include <fcntl.h> /* for open files*/

#include "macros.h" /* for msg help and prompt */

/**
 * struct info- struct for the program's data
 * @myprogram: the name of the executable
 * @lineptr: pointer to the input read for _getline
 * @cmd_name: pointer to the first command typed by the user
 * @execution_count: number of excecuted comands
 * @fd: file descriptor to the input of commands
 * @tokens: pointer to array of tokenized input
 * @env: copy of the environ
 * @aliases: array of pointers with aliases.
 */
typedef struct info
{
	char *myprogram;
	char *lineptr;
	char *cmd_name;
	int execution_count;
	int fd;
	char **tokens;
	char **env;
	char **aliases;
} shell_data;

/**
 * struct builtins - struct for the builtins
 * @builtin: the name of the builtin
 * @function: the associated function to be called for each builtin
 */
typedef struct builtins
{
	char *builtin;
	int (*function)(shell_data *data);
} builtins;


void init_data(shell_data *data, int arc, char *argv[], char **env);

void itrator(char *prompt, shell_data *data);

void _ctrl_c(int opr UNUSED);


int _readInput(shell_data *data);

int ops_handle(char *array_commands[], int i, char array_operators[]);


void expand_variables(shell_data *data);

void expand_alias(shell_data *data);

int buffer_add(char *buffer, char *str_to_add);


void tokenize(shell_data *data);

char *_strtok(char *line, char *delim);

int execute(shell_data *data);


int builtins_list(shell_data *data);


char **tokenize_path(shell_data *data);

int find_program(shell_data *data);


void free_array_of_pointers(char **directories);

void free_recurrent_data(shell_data *data);

void free_all_data(shell_data *data);


int builtin_exit(shell_data *data);

int builtin_cd(shell_data *data);

int set_work_directory(shell_data *data, char *new_dir);

int builtin_help(shell_data *data);

int builtin_alias(shell_data *data);

int builtin_env(shell_data *data);

int builtin_set_env(shell_data *data);

int builtin_unset_env(shell_data *data);

char *env_get_key(char *name, shell_data *data);

int env_set_key(char *key, char *value, shell_data *data);

int env_remove_key(char *key, shell_data *data);

void print_environ(shell_data *data);

int _print(char *string);

int _printe(char *string);

int _print_error(int errorcode, shell_data *data);

int str_length(char *string);

char *dup_str(char *string);

int str_compare(char *string1, char *string2, int number);

char *str_concat(char *string1, char *string2);

void str_reverse(char *string);

void long_to_string(long number, char *string, int base);

int _atoi(char *s);

int count_characters(char *string, char *character);

int print_alias(shell_data *data, char *alias);

char *get_alias(shell_data *data, char *alias);

int set_alias(char *alias_string, shell_data *data);


#endif /* SHELL_H */
