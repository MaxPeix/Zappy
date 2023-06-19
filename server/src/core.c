/*
** EPITECH PROJECT, 2023
** core_server
** File description:
** core
*/

#include "server.h"

void handle_commands(client_t *clients, client_t *client,
    server_params_t *server_params, command_t cmd)
{
    handle_incantation_command(clients, client, server_params, cmd.args);
    if (client->is_elevating == 1)
        return;
    handle_command(client, server_params, cmd.args);
    handle_connect_nbr_command(clients, client, server_params, cmd.args);
    handle_command_with_player_nbr(clients, client, server_params, cmd.args);
    handle_broadcast_command(clients, client, cmd.args);
    handle_eject_command(clients, client, server_params, cmd.args);
    handle_fork_command(client, clients, server_params, cmd.args);
    handle_look_command(clients, client, server_params, cmd.args);
}

void execute_commands_if_ready(client_t *clients, client_t *client,
    server_params_t *server_params)
{
    if (!clients || !client || !server_params)
        return;
    command_t *tmp = client->commands;
    while (tmp != NULL && tmp->executed == 1)
        tmp = tmp->next;
    if (tmp == NULL)
        return;
    if (time(NULL) >= tmp->execution_time && tmp->executed == 0) {
        handle_commands(clients, client, server_params, *tmp);
        tmp->executed = 1;
    }
}

void check_lose_food(client_t *client, server_params_t *server_params)
{
    if (!client || !server_params)
        return;
    if (client->is_graphical == 1 || client->is_connected == 0)
        return;
    if (time(NULL) >= client->food_losing_timer) {
        client->food -= 1;
        client->food_losing_timer = time(NULL)
            + 126 / server_params->frequency;
        printf("Client %d lost 1 food\n", client->id);
    }
}

void check_client_activity(client_t *clients,
    int server_socket, fd_set *readfds, server_params_t *server_params)
{
    int client_socket = 0;
    int valread = 0;
    char buffer[BUFFER_SIZE] = {0};
    for (int i = 0; i < MAX_CLIENTS; i++) {
        client_socket = clients[i].socket;
        check_lose_food(&clients[i], server_params);
        execute_commands_if_ready(clients, &clients[i], server_params);
        check_death_player(clients, &clients[i], server_params);
        if (!FD_ISSET(client_socket, readfds))
            continue;
        valread = read(client_socket, buffer, BUFFER_SIZE - 1);
        if (valread <= 0 ) {
            handle_disconnect(&clients[i], server_params);
            continue;
        }
        buffer[valread] = '\0';
        if (strcmp(buffer, "\n") == 0) {
            send_response(client_socket, "ko\n");
            continue;
        }
        handle_client_request(clients, buffer, &clients[i], server_params);
    }
}
