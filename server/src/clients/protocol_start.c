/*
** EPITECH PROJECT, 2023
** protocol_start
** File description:
** protocol_start
*/

#include "server.h"

int check_team_name(char *team_name, char **valid_teams)
{
    for (int i = 0; valid_teams[i]; i++) {
        printf("valid team: %s, team_name: %s.\n", valid_teams[i], team_name);
        if (strcasecmp(team_name, valid_teams[i]) == 0)
            return 1;
    }
    return 0;
}

void send_team_info(int socket, client_t *client, server_params_t
    server_params)
{
    char slots_str[50];
    char world_dimensions_str[50];

    if (check_team_name(client->team_name, server_params.team_names)) {
        sprintf(slots_str, "%d\n", server_params.clients_per_team);
        send_response(socket, slots_str);
        sprintf(world_dimensions_str, "%d %d\n", server_params.width,
            server_params.height);
        send_response(socket, world_dimensions_str);
    } else
        send_response(socket, "ko\n");
}
