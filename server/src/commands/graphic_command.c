/*
** EPITECH PROJECT, 2023
** handle_command
** File description:
** graphic_command
*/

#include "server.h"

void print_bct(server_params_t *server_params, client_t *client)
{
    char buffer_bct[200];

    for (int i = 0; i < server_params->height; i++) {
        for (int j = 0; j < server_params->width; j++) {
            sprintf(buffer_bct, "bct %d %d %d %d %d %d %d %d %d\n", j, i,
                    server_params->world[i][j].food,
                    server_params->world[i][j].linemate,
                    server_params->world[i][j].deraumere,
                    server_params->world[i][j].sibur,
                    server_params->world[i][j].mendiane,
                    server_params->world[i][j].phiras,
                    server_params->world[i][j].thystame);
            send_response(client->socket, buffer_bct);
        }
    }
}

void handle_graphic_command(client_t *client, server_params_t *server_params)
{
    char buffer_map_size[50];
    char buffer_sgt[50];
    sprintf(buffer_map_size, "msz %d %d\n", server_params->width,
        server_params->height);
    sprintf(buffer_sgt, "sgt %d\n", server_params->frequency);
    send_response(client->socket, buffer_map_size);
    send_response(client->socket, buffer_sgt);
    print_bct(server_params, client);
    if (!server_params->team_names)
        return;
    for (int i = 0; server_params->team_names[i]; i++) {
        send_response(client->socket, "tna ");
        send_response(client->socket, server_params->team_names[i]);
        send_response(client->socket, "\n");
    }
    return;
}
