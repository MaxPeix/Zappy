/*
** EPITECH PROJECT, 2023
** init_client
** File description:
** init
*/

#include "server.h"

void init_clients_list(client_t *clients)
{
    for (int i = 0; i < MAX_CLIENTS; i++) {
        clients[i].socket = 0;
        clients[i].id = i + 1;
        clients[i].start_loggin = 0;
        clients[i].is_graphical = 0;
        clients[i].team_name = NULL;
        clients[i].level = 1;
        clients[i].x_position = 0;
        clients[i].y_position = 0;
        clients[i].orientation = SOUTH;
    }
}

void handle_disconnect(client_t *client)
{
    close(client->socket);
    client->socket = 0;
    client->start_loggin = 0;
    if (client->team_name)
        free(client->team_name);
    client->team_name = NULL;
    client->is_graphical = 0;
    client->level = 1;
    client->x_position = 0;
    client->y_position = 0;
    client->orientation = SOUTH;
}
