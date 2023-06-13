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
    if (args == NULL) {
        printf("args is NULL. Exiting duplicate_args\n");
        return NULL;
    }
    int arg_count = 0;
    while (args[arg_count] != NULL)
        arg_count++;
    char **new_args = calloc(arg_count + 1, sizeof(char *));
    if (new_args == NULL)
        return NULL;
    int i = 0;
    for (i = 0; i < arg_count; i++) {
        new_args[i] = msprintf("%s", args[i]);
        if (new_args[i] == NULL)
            break;
    }
    if (i != arg_count) {
        for (int j = 0; j < i; j++)
            free(new_args[j]);
        free(new_args);
        return NULL;
    }
    new_args[arg_count] = NULL;
    return new_args;
}

void remove_executed_command(client_t *client, int command_index)
{
    if (!client || !client->commands)
        return;
    if (command_index < 0 || command_index >= client->command_count)
        return;
    for (int k = command_index; k < client->command_count - 1; k++)
        client->commands[k] = client->commands[k + 1];
    client->command_count--;
    command_t *new_commands =
        realloc(client->commands, sizeof(command_t) * client->command_count);
    if (new_commands == NULL && client->command_count > 0) {
        free(client->commands);
        client->commands = NULL;
    } else
        client->commands = new_commands;
}

void add_command_to_client(client_t *client, command_t *new_command)
{
    if (!client || !new_command)
        return;
    command_t *new_commands = realloc(client->commands,
        sizeof(command_t) * (client->command_count + 1));
    if (!new_commands) {
        free(new_command);
        return;
    }
    client->commands = new_commands;
    client->commands[client->command_count] = *new_command;
    client->command_count++;
}
