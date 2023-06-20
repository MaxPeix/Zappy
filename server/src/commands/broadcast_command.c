/*
** EPITECH PROJECT, 2023
** broadcast command
** File description:
** broadcast_command
*/

#include "server.h"

char *build_message(char **args)
{
    char *message = NULL;
    for (int i = 1; args[i] != NULL; i++) {
        if (message == NULL) {
            message = strdup(args[i]);
        } else {
            char *new_message = NULL;
            new_message = msprintf("%s %s", message, args[i]);
            free(message);
            message = new_message;
        }
    }
    return message;
}

void send_to_graphical_clients(client_t *clients, char *output)
{
    for (int i = 0; i < MAX_CLIENTS; i++)
        if (clients[i].is_graphical == 1 && clients[i].is_connected == 1)
            send_response(clients[i].socket, output);
}

void send_broadcast_to_clients(client_t *clients, client_t *client,
    char *message, server_params_t *server_params)
{
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (clients[i].is_connected == 0 || clients[i].is_graphical == 1
            || clients[i].is_dead == 1 || clients[i].id == client->id)
            continue;
        char *output = NULL;
        coord_params_t params;
        params.x1 = client->x_position;
        params.y1 = client->y_position;
        params.x2 = clients[i].x_position;
        params.y2 = clients[i].y_position;
        params.width = server_params->width;
        params.height = server_params->height;
        int distance = manhattan_distance_torus(params);
        int tile_number = identify_tile(client, &clients[i], params);
        output = msprintf("message %d %s\n", tile_number, message);
        dprintf(clients[i].socket, "%s", output);
        free(output);
    }
}

void handle_broadcast_command(client_t *clients,
    client_t *client, char **args, server_params_t *server_params)
{
    if (!args || !client)
        return;
    if (args[0] == NULL)
        return;
    if (strcmp(args[0], "Broadcast") == 0) {
        if (args[1] == NULL)
            return send_response(client->socket, "ko\n");
        char *message = build_message(args);
        if (!message)
            return;
        char *output = msprintf("pbc %d %s\n", client->id, message);
        if (!output)
            return;
        send_to_graphical_clients(clients, output);
        send_broadcast_to_clients(clients, client, message, server_params);
        send_response(client->socket, "ok\n");
        free(output);
        free(message);
    }
}
