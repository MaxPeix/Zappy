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
        clients[i].id = i;
        clients[i].start_loggin = 0;
        clients[i].is_graphical = 0;
        clients[i].team_name = NULL;
        clients[i].level = 1;
        clients[i].x_position = 0;
        clients[i].y_position = 0;
        clients[i].orientation = SOUTH;
        clients[i].food = 10;
        clients[i].linemate = 0;
        clients[i].deraumere = 0;
        clients[i].sibur = 0;
        clients[i].mendiane = 0;
        clients[i].phiras = 0;
        clients[i].thystame = 0;
        clients[i].incantation_level = 0;
        clients[i].is_connected = 0;
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
    client->food = 10;
    client->linemate = 0;
    client->deraumere = 0;
    client->sibur = 0;
    client->mendiane = 0;
    client->phiras = 0;
    client->thystame = 0;
    client->incantation_level = 0;
    client->is_connected = 0;
}
