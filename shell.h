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

/************* MACROS **************/

#include "macros.h" /* for msg help and prompt */

/************* STRUCTURES **************/

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


/************* MAIN FUNCTIONS *************/


/*========  shell.c  ========*/

/* Inicialize the struct with the info of the program */
void init_data(shell_data *data, int arc, char *argv[], char **env);

/* Makes the infinite loop that shows the prompt*/
void itrator(char *prompt, shell_data *data);

/* Print the prompt in a new line */
void _ctrl_c(int opr UNUSED);


/*========  custom_input.c  ========*/

/* custom function that takes input from the user*/
int _readInput(shell_data *data);

/* split the each line for the logical operators if it exist */
int ops_handle(char *array_commands[], int i, char array_operators[]);


/*======== expansions.c ========*/

/* expand variables */
void expand_variables(shell_data *data);

/* expand aliases */
void expand_alias(shell_data *data);

/* append the string to the end of the buffer*/
int buffer_add(char *buffer, char *str_to_add);


/*======== str_tok.c ========*/

/* Separate the string in tokens using a designed delimiter */
void tokenize(shell_data *data);

/* Creates a pointer to a part of a string */
char *_strtok(char *line, char *delim);


/*======== execute.c ========*/

/* Execute a command with its entire path */
int execute(shell_data *data);


/*======== builtins_list.c ========*/

/* If match a builtin, executes it */
int builtins_list(shell_data *data);


/*======== find_in_path.c ========*/

/* Creates an array of the path directories */
char **tokenize_path(shell_data *data);

/* Search for program in path */
int find_program(shell_data *data);


/************** HELPERS FOR MEMORY MANAGEMENT **************/


/*======== helpers_free.c ========*/

/* Frees the memory for directories */
void free_array_of_pointers(char **directories);

/* Free the fields needed each loop */
void free_recurrent_data(shell_data *data);

/* Free all field of the data */
void free_all_data(shell_data *data);


/************** BUILTINS **************/


/*======== builtins_more.c ========*/

/* Close the shell */
int builtin_exit(shell_data *data);

/* Change the current directory */
int builtin_cd(shell_data *data);

/* set the work directory */
int set_work_directory(shell_data *data, char *new_dir);

/* show help information */
int builtin_help(shell_data *data);

/* set, unset and show alias */
int builtin_alias(shell_data *data);


/*======== builtins_env.c ========*/

/* Shows the environment where the shell runs */
int builtin_env(shell_data *data);

/* create or override a variable of environment */
int builtin_set_env(shell_data *data);

/* delete a variable of environment */
int builtin_unset_env(shell_data *data);


/************** HELPERS FOR ENVIRONMENT VARIABLES MANAGEMENT **************/


/*======== env_management.c ========*/

/* Gets the value of an environment variable */
char *env_get_key(char *name, shell_data *data);

/* Overwrite the value of the environment variable */
int env_set_key(char *key, char *value, shell_data *data);

/* Remove a key from the environment */
int env_remove_key(char *key, shell_data *data);

/* prints the current environ */
void print_environ(shell_data *data);


/************** HELPERS FOR PRINTING **************/


/*======== helpers_print.c ========*/

/* Prints a string in the standar output */
int _print(char *string);

/* Prints a string in the standar error */
int _printe(char *string);

/* Prints a string in the standar error */
int _print_error(int errorcode, shell_data *data);


/************** HELPERS FOR STRINGS MANAGEMENT **************/


/*======== helpers_string.c ========*/

/* Counts the number of characters of a string */
int str_length(char *string);

/* Duplicates an string */
char *dup_str(char *string);

/* Compares two strings */
int str_compare(char *string1, char *string2, int number);

/* Concatenates two strings */
char *str_concat(char *string1, char *string2);

/* Reverse a string */
void str_reverse(char *string);


/*======== helpers_numbers.c ========*/

/* Cast from int to string */
void long_to_string(long number, char *string, int base);

/* convert an string in to a number */
int _atoi(char *s);

/* count the coincidences of character in string */
int count_characters(char *string, char *character);


/*======== alias_management.c ========*/

/* print the list of alias */
int print_alias(shell_data *data, char *alias);

/* get the alias name */
char *get_alias(shell_data *data, char *alias);

/* set the alias name */
int set_alias(char *alias_string, shell_data *data);


#endif /* SHELL_H */
