/*
** EPITECH PROJECT, 2023
** server
** File description:
** fork_command.c
*/

#include "server.h"

void handle_fork_command(client_t *client, server_params_t *server_params,
                         char **args)
{
    tile_t *tile =
        &server_params->world[client->y_position][client->x_position];
    if (strcasecmp(args[0], "FORK") == 0) {
        server_params->clients_per_team++;
        tile->eggs++;
        send_response(client->socket, "ok\n");
    }
}
