/*
** EPITECH PROJECT, 2023
** server
** File description:
** fork_command.c
*/

#include "server.h"

void update_client_per_team_after_fork(client_t *client, client_t *clients)
{
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (clients[i].is_connected == 1
            && strcasecmp(client->team_name, clients[i].team_name) == 0)
            client->team_max_clients++;
    }
}

void handle_fork_command(client_t *client,
    client_t *clients, server_params_t *server_params, char **args)
{
    tile_t *tile =
        &server_params->world[client->y_position][client->x_position];
    if (strcasecmp(args[0], "FORK") == 0) {
        tile->eggs++;
        send_response(client->socket, "ok\n");
    }
}
