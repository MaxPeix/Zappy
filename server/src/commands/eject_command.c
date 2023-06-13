/*
** EPITECH PROJECT, 2023
** broadcast command
** File description:
** broadcast_command
*/

#include "server.h"

void send_eject_response_to_graphical_clients(client_t *clients,
    int client_id)
{
    char *output_graphical = NULL;

    for (int index = 0; index < MAX_CLIENTS; index++) {
        if (clients[index].is_graphical == 1
            && clients[index].is_connected == 1) {
            output_graphical = msprintf("pex %d\n", client_id);
            send_response(clients[index].socket, output_graphical);
            free(output_graphical);
        }
    }
}

int send_eject_response_to_clients_at_same_position(client_t *clients,
    client_t *client, server_params_t *server_params)
{
    int ejected = 0;
    int x = client->x_position;
    int y = client->y_position;
    int id = client->id;
    int orientation = client->orientation;
    char *output_ejected_player = NULL;

    output_ejected_player = msprintf("eject: %d\n", orientation);
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (clients[i].x_position == x && clients[i].y_position == y
            && clients[i].id != id && clients[i].is_connected == 1
            && clients[i].is_graphical == 0) {
            send_response(clients[i].socket, output_ejected_player);
            update_client_position(&clients[i], orientation, server_params);
            send_eject_response_to_graphical_clients(clients, clients[i].id);
            ejected += 1;
        }
    }
    free(output_ejected_player);
    return ejected;
}

void handle_eject_command(client_t *clients, client_t *client,
    server_params_t *server_params, char **args)
{
    char *output_ejected_player = NULL;
    int ejected = 0;

    if (strcasecmp(args[0], "EJECT") == 0) {
        ejected =
            send_eject_response_to_clients_at_same_position(
                clients, client, server_params);
        if (ejected == 0)
            send_response(client->socket, "ko\n");
        else {
            server_params->
                world[client->y_position][client->x_position].eggs = 0;
            send_response(client->socket, "ok\n");
        }
        free(output_ejected_player);
    }
}
