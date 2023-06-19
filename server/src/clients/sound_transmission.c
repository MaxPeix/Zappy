/*
** EPITECH PROJECT, 2023
** sound_transmission
** File description:
** sound_transmission
*/

#include "server.h"

void send_sound_to_graphical_clients(client_t *clients, int client_id)
{
    char *output_graphical = NULL;

    for (int index = 0; index < MAX_CLIENTS; index++) {
        if (clients[index].is_graphical == 1
            && clients[index].is_connected == 1) {
            output_graphical = msprintf("pic %d\n", client_id);
            send_response(clients[index].socket, output_graphical);
            free(output_graphical);
        }
    }
}
