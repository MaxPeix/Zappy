/*
** EPITECH PROJECT, 2023
** checklogi
** File description:
** check_login
*/

#include "server.h"

void check_login(client_t *clients, int i, char *buffer)
{
    int client_socket = clients[i].socket;
    if (strncmp(buffer, "QUIT", 4) == 0) {
        send_response(client_socket, "Goodbye.\n");
        handle_disconnect(clients, clients[i].socket, i);
        return;
    }
    clients[i].logged_in = 1;
}
