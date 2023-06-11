/*
** EPITECH PROJECT, 2023
** server
** File description:
** client_command.c
*/

#include "server.h"

static void print_connect_nbr(server_params_t *server_params,
                              client_t *client,
                              client_t *clients)
{
    int count = 0;

    for (int i = 0; i < server_params->clients_per_team; i++) {
        if (clients[i].is_connected == 1 && clients[i].team_name != NULL
            && strcmp(clients[i].team_name, client->team_name) == 0)
            count++;
    }
    dprintf(client->socket, "%d\n", server_params->clients_per_team - count);
}

void handle_connect_nbr_command(client_t *clients,
                                client_t *client,
                                server_params_t *server_params,
                                char **args)
{
    if (strcasecmp(args[0], "CONNECT_NBR") == 0) {
        print_connect_nbr(server_params, client, clients);
        return;
    }
}
