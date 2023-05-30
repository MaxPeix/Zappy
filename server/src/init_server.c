/*
** EPITECH PROJECT, 2023
** init_server
** File description:
** init_server
*/

#include "server.h"

server_params_t init_default_server_params(void)
{
    server_params_t params;

    params.port = 0;
    params.width = 0;
    params.height = 0;
    params.team_names = NULL;
    params.clients_per_team = 0;
    params.frequency = 0;
    return params;
}

void parse_args(int argc, char **argv, server_params_t *params)
{
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-p") == 0) {
            params->port = atoi(argv[++i]);
        } else if (strcmp(argv[i], "-x") == 0) {
            params->width = atoi(argv[++i]);
        } else if (strcmp(argv[i], "-y") == 0) {
            params->height = atoi(argv[++i]);
        } else if (strcmp(argv[i], "-n") == 0) {
            params->team_names = &argv[i + 1];
            break;
        } else if (strcmp(argv[i], "-c") == 0) {
            params->clients_per_team = atoi(argv[++i]);
        } else if (strcmp(argv[i], "-f") == 0) {
            params->frequency = atoi(argv[++i]);
        }
    }
}

int create_and_bind_socket(server_params_t params,
    struct sockaddr_in *address)
{
    if (params.port == 0 || !address)
        return -1;
    int server_socket;
    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket failed");
        return -1;
    }
    address->sin_family = AF_INET;
    address->sin_addr.s_addr = INADDR_ANY;
    address->sin_port = htons(params.port);
    if (bind(server_socket,
        (struct sockaddr *)address, sizeof(*address)) < 0) {
        perror("bind failed");
        return -1;
    }
    printf("Port : %d\n", params.port);
    return server_socket;
}
