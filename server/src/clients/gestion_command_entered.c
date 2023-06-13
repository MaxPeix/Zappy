/*
** EPITECH PROJECT, 2023
** gestion client command entered
** File description:
** gestion_command_entered
*/

#include "server.h"
#include <time.h>

command_info_t commands_list[] = {
    {"Broadcast", 7.0},
    {"Forward", 7.0},
    {"Right", 7.0},
    {"Left", 7.0},
    {"Look", 7.0},
    {"Inventory", 1.0},
    {"Connect_nbr", 0.0},
    {"Fork", 42.0},
    {"Eject", 7.0},
    {"Take", 7.0},
    {"Set", 7.0},
    {"Incantation", 300.0},
    {"msz", 0.0},
    {"bct", 0.0},
    {"mct", 0.0},
    {"tna", 0.0},
    {"ppo", 0.0},
    {"plv", 0.0},
    {"pin", 0.0},
    {"sgt", 0.0},
    {"sst", 0.0},
    {NULL, 0.0},
};

command_t *create_new_command(char **args, server_params_t *server_params)
{
    command_t *new_command = calloc(1, sizeof(command_t));
    if (!new_command)
        return NULL;
    if (!args || !server_params) {
        return NULL;
    }
    if (!args[0]) {
        if (new_command)
            free(new_command);
        return NULL;
    }
    new_command->name = strdup(args[0]);
    new_command->args = duplicate_args(args);
    if (!new_command->name || !new_command->args) {
        if (new_command->name)
            free(new_command->name);
        if (new_command->args)
            free_command_args(new_command->args);
        if (new_command)
            free(new_command);
        return NULL;
    }
    for (command_info_t *command = commands_list; command->name; ++command) {
        if (strcmp(new_command->name, command->name) == 0) {
            new_command->execution_time = time(NULL) +
                command->execution_time_factor / server_params->frequency;
            return new_command;
        }
    }
    free_command_args(new_command->args);
    if (new_command->name && strlen(new_command->name) > 0)
        free(new_command->name);
    return NULL;
}

void handle_client_request(client_t *clients,
    char *buffer, int i, server_params_t *server_params)
{
    if (!buffer || strlen(buffer) == 0)
        return;
    char **args = get_args_from_buffer(buffer);
    if (args == NULL)
        return;
    if (args[0] == NULL) {
        free_array(args);
        return;
    }
    char *output_incantation = NULL;
    if (strcmp(args[0], "Incantation") == 0) {
        if (can_do_incantation(clients, &clients[i],
            server_params, args) == 0) {
            output_incantation = msprintf("ko\n");
            send_response(clients[i].socket, output_incantation);
            free(output_incantation);
            free_array(args);
            return;
        }
        send_message_to_graphical_start_incantation(clients,
            &clients[i], server_params, args);
    }
    command_t *new_command = create_new_command(args, server_params);
    if (!new_command) {
        send_response(clients[i].socket, "ko\n");
        return;
    }

    add_command_to_client(&clients[i], new_command);
    free_array(args);
}
