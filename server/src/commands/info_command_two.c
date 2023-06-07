/*
** EPITECH PROJECT, 2023
** projets
** File description:
** info_command
*/

#include "server.h"

void print_ppo(client_t *client, client_t *player)
{
    char *output = NULL;
    if (!player || !client) {
        printf("Error: player or client is NULL\n");
        return;
    }
    output = msprintf("ppo %d %d %d %d\n", player->id,
        player->x_position, player->y_position, player->orientation);
    if (!output) {
        printf("Error: Could not allocate memory for output string\n");
        return;
    }
    send_response(client->socket, output);
    if (output)
        free(output);
}

void handle_command_with_player_nbr(client_t *clients, client_t *client,
    server_params_t *server_params, char **args)
{
    if (!args[0] || !args[1])
        return;  
    int player_id = atoi(args[1]);
    client_t *player = NULL;
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (clients[i].id == player_id) {
            player = &clients[i];
            break;
        }
    }
    if (strcasecmp(args[0], "PPO") == 0) {
        if (player == NULL) {
            send_response(client->socket, "ko\n");
            return;
        }
        print_ppo(client, player);
        return;
    }
    printf("fin de handle_command_with_player_nbr\n");
}
