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
        clients[i].start_loggin = 0;
        clients[i].is_graphical = 0;
        clients[i].team_name = NULL;
        clients[i].level = 1;
    }
}

void handle_disconnect(client_t *client)
{
    close(client->socket);
    client->socket = 0;
    client->start_loggin = 0;
    client->is_graphical = 0;
    client->team_name = NULL;
    client->level = 1;
}
