/*
** EPITECH PROJECT, 2023
** B-YEP-400-BDX-4-1-zappy-max.peixoto
** File description:
** check_win_event.c
*/

#include "server.h"

void check_win_event(client_t client, client_t *clients,
                     server_params_t *server_params)
{
    int team_count = 0;
    int *team = NULL;

    for (;server_params->team_names[team_count] != NULL; team_count++);
    team = malloc(sizeof(int) * team_count);
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (clients[i].is_graphical == 0 || clients[i].is_connected == 0
            || clients[i].is_dead == 1)
            continue;
        if (clients[i].level == 8) {
            for (int j = 0; j < team_count; j++)
                if (strcmp(clients[i].team_name, server_params->team_names[j]) == 0)
                    team[j] += 1;
        }
    }
    for (int i = 0; i < team_count; i++)
        if (team[i] >= 6) {
            send_message_to_graphical(clients, "seg\n");
            return;
        }
}
