/*
** EPITECH PROJECT, 2023
** server
** File description:
** fork_command.c
*/

#include "server.h"

void update_client_per_team_after_fork(client_t *client, client_t *clients)
{
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (clients[i].is_connected == 0 || clients[i].is_graphical == 1)
            continue;
        if (strcasecmp(client->team_name, clients[i].team_name) == 0) {
            client->team_max_clients++;
            return;
        }
    }
}

void handle_fork_command(client_t *client,
    client_t *clients, server_params_t *server_params, char **args)
{
    tile_t *tile =
        &server_params->world[client->y_position][client->x_position];
    char *output_graphical = NULL;
    if (strcasecmp(args[0], "FORK") == 0) {
        update_client_per_team_after_fork(client, clients);
        int length = 0;
        if (tile->eggs)
            for (; tile->eggs[length] != 0; ++length);
        tile->eggs = realloc(tile->eggs, (length + 2) * sizeof(int));
        if (!tile->eggs) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(EXIT_FAILURE);
        }
        int previous_value = (length > 0) ? tile->eggs[length - 1] : 0;
        tile->eggs[length] = previous_value + 1;
        tile->eggs[length + 1] = 0;
        char *output_graphical =
            msprintf("enw %d %d %d %d\n", tile->eggs[length],
                client->id, client->x_position, client->y_position);
        send_message_to_graphical(clients, output_graphical);
        free(output_graphical);
        send_response(client->socket, "ok\n");
    }
}
