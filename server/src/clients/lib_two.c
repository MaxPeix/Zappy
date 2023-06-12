/*
** EPITECH PROJECT, 2023
** lib_two_functions
** File description:
** lib_two
*/

#include "server.h"

void free_command_args(char **args)
{
    for (int i = 0; args[i] != NULL; i++)
        free(args[i]);
    free(args);
}

char **duplicate_args(char **args)
{
    int arg_count = 0;
    while (args[arg_count] != NULL)
        arg_count++;

    char **new_args = malloc(sizeof(char*) * (arg_count + 1));

    for (int i = 0; i < arg_count; i++)
        new_args[i] = strdup(args[i]);

    new_args[arg_count] = NULL;

    return new_args;
}

void remove_executed_command(client_t *client, int command_index)
{
    for (int k = command_index; k < client->command_count - 1; k++)
        client->commands[k] = client->commands[k + 1];
    free_command_args(client->commands[client->command_count - 1].args);
    client->command_count--;
    client->commands = realloc(client->commands,
        sizeof(command_t) * client->command_count);
}

void add_command_to_client(client_t *client, command_t *new_command)
{
    client->commands = realloc(client->commands, sizeof(command_t)
        * (client->command_count + 1));
    client->commands[client->command_count] = *new_command;
    client->command_count++;
    free(new_command);
}
