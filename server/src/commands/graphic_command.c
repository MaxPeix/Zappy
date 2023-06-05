/*
** EPITECH PROJECT, 2023
** handle_command
** File description:
** graphic_command
*/

#include "server.h"

void handle_graphic_command(client_t *client, server_params_t server_params)
{
    char buffer_map_size[50];
    char buffer_sgt[50];
    sprintf(buffer_map_size, "msz %d %d\n", server_params.width,
        server_params.height);
    sprintf(buffer_sgt, "sgt %d\n", server_params.frequency);
    send_response(client->socket, buffer_map_size);
    send_response(client->socket, buffer_sgt);
    send_response(client->socket, "BCT: TO DO\n");
    if (!server_params.team_names)
        return;
    for (int i = 0; server_params.team_names[i]; i++) {
        send_response(client->socket, "tna ");
        send_response(client->socket, server_params.team_names[i]);
        send_response(client->socket, "\n");
    }
    return;
}
