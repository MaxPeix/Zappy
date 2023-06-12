/*
** EPITECH PROJECT, 2023
** lib_handle_command
** File description:
** handle_command_lib
*/

#include "server.h"

char **add_arg_to_list(char **args, char *command, int command_count)
{
    char **temp = realloc(args, sizeof(char *) * (command_count + 1));
    if (temp == NULL) {
        free_array(args);
        return NULL;
    }
    args = temp;
    args[command_count] = strdup(command);
    if (args[command_count] == NULL) {
        free_array(args);
        return NULL;
    }
    return args;
}

char **get_args_from_buffer(char *buffer)
{
    char **args = NULL;
    char *command = NULL;
    int command_count = 0;

    if (!buffer)
        return NULL;
    command = strtok(buffer, " \r\n");
    while (command != NULL) {
        args = add_arg_to_list(args, command, command_count);
        if (args == NULL)
            return NULL;
        command = strtok(NULL, " \r\n");
        command_count++;
    }
    args[command_count] = NULL;
    return args;
}

void free_array(char **array)
{
    if (!array)
        return;
    for (int i = 0; array[i]; i++)
        free(array[i]);
    free(array);
}
