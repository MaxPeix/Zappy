/*
** EPITECH PROJECT, 2023
** lib_two_functions
** File description:
** lib_two
*/

#include "server.h"

void free_command_executed(command_t *command)
{
    if (command) {
        if (command->name) {
            free(command->name);
            command->name = NULL;
        }
        if (command->args) {
            free_command_args(command->args);
            command->args = NULL;
        }
    }
}

// void remove_executed_command(client_t *client, int command_index)
// {
//     if (!client || !client->commands)
//         return;
//     if (command_index < 0 || command_index >= client->command_count)
//         return;

//     printf("Removing command %s\n", client->commands[command_index].name);
//     free_command_executed(&client->commands[command_index]);
//     memset(&client->commands[command_index], 0, sizeof(command_t));
//     for (int k = command_index; k < client->command_count - 1; k++)
//         client->commands[k] = client->commands[k + 1];
//     client->command_count--;
//     command_t *new_commands =
//         realloc(client->commands, sizeof(command_t) * client->command_count);
//     if (new_commands == NULL && client->command_count > 0) {
//         free(client->commands);
//         client->commands = NULL;
//     } else
//         client->commands = new_commands;
// }
