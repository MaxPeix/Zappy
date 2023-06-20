/*
** EPITECH PROJECT, 2023
** B-YEP-400-BDX-4-1-zappy-max.peixoto
** File description:
** check_win_event.c
*/

#include "server.h"

void send_win_to_client(client_t *client, const client_t *clients)
{
    printf("Client %d won\n", (*client).id);
    for (int j = 0; j < MAX_CLIENTS; j++)
        if (clients[j].is_graphical == 1)
            send_response(clients[j].socket, "You win!\n");
}

void check_win_event(client_t client, client_t *clients,
                     server_params_t *server_params)
{
    int nb_lvl_8 = 0;

    if (!clients || !server_params ||client.is_graphical == 1
        || client.is_connected == 0 || client.is_dead == 1)
        return;
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (clients[i].is_graphical == 1 || clients[i].is_connected == 0
            || clients[i].is_dead == 1)
            continue;
        if (clients[i].level == 8)
            nb_lvl_8 += 1;
        if (nb_lvl_8 >= 6) {
            send_message_to_graphical(clients, "seg\n");
            send_win_to_client(&client, clients);
        }
    }
}