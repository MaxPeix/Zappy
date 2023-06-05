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
        clients[i].available_slots = 1;
    }
}
