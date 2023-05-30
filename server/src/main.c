/*
** EPITECH PROJECT, 2023
** zappy main$
** File description:
** main
*/

#include "server.h"

void print_params(server_params_t params)
{
    printf("Port: %d\n", params.port);
    printf("Width: %d\n", params.width);
    printf("Height: %d\n", params.height);
    printf("Clients per Team: %d\n", params.clients_per_team);
    printf("Frequency: %d\n", params.frequency);

    printf("Team Names:\n");
    for (int i = 0; params.team_names[i]; i++)
        printf("- %s\n", params.team_names[i]);
}

int main(int argc, char **argv)
{
    server_params_t params = init_default_server_params();
    parse_args(argc, argv, &params);
    int errorChecked = check_errors(argc, argv, params);
    if (errorChecked == 84)
        return EPITECH_ERROR;
    if (errorChecked == 1)
        return 0;
    print_params(params);
    client_t *clients = malloc(sizeof(client_t) * MAX_CLIENTS);
    struct sockaddr_in address;
    init_clients_list(clients);
    int server_socket = create_and_bind_socket(params, &address);
    if (server_socket == -1)
        return EPITECH_ERROR;
    if (listen(server_socket, 3) < 0)
        return EPITECH_ERROR;
    wait_for_connections(server_socket, clients, address);
    return 0;
}
