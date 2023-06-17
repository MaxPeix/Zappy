/*
** EPITECH PROJECT, 2023
** init_client
** File description:
** init
*/

#include "server.h"
#include <stdlib.h>

int generate_rand_position(int upper_limit)
{
    return rand() % upper_limit;
}

void init_cliens_list_two(client_t *clients, int i,
    server_params_t *server_params)
{
    clients[i].deraumere = 0;
    clients[i].sibur = 0;
    clients[i].mendiane = 0;
    clients[i].phiras = 0;
    clients[i].thystame = 0;
    clients[i].is_connected = 0;
    clients[i].is_dead = 0;
    clients[i].team_max_clients = server_params->clients_per_team;
}

void init_clients_list(client_t *clients, server_params_t *server_params)
{
    for (int i = 0; i < MAX_CLIENTS; i++) {
        clients[i].socket = 0;
        clients[i].id = i;
        clients[i].start_loggin = 0;
        clients[i].is_graphical = 0;
        clients[i].team_name = NULL;
        clients[i].level = 1;
        clients[i].x_position = generate_rand_position(server_params->width);
        clients[i].y_position = generate_rand_position(server_params->height);
        clients[i].orientation = SOUTH;
        clients[i].food = 10;
        clients[i].linemate = 0;
        init_cliens_list_two(clients, i, server_params);
    }
}

void handle_disconnect_two(client_t *client, server_params_t *server_params)
{
    client->x_position = generate_rand_position(server_params->width);
    client->y_position = generate_rand_position(server_params->height);
    client->sibur = 0;
    client->mendiane = 0;
    client->phiras = 0;
    client->thystame = 0;
    client->is_connected = 0;
    client->is_dead = 0;
    client->team_max_clients = server_params->clients_per_team;
}

void handle_disconnect(client_t *client, server_params_t *server_params)
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
    handle_disconnect_two(client, server_params);
}
