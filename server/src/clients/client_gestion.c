/*
** EPITECH PROJECT, 2023
** gestion clients
** File description:
** client_gestion
*/

#include "server.h"

int set_clients_sockets(client_t *clients, fd_set *readfds, int server_socket)
{
    int max_sd = server_socket;
    int sd;
    for (int i = 0; i < MAX_CLIENTS; i++) {
        sd = clients[i].socket;
        if (sd > 0)
            FD_SET(sd, readfds);
        if (sd > max_sd)
            max_sd = sd;
    }
    return max_sd;
}

int accept_new_connection(int server_socket, struct sockaddr_in address)
{
    int addrlen = sizeof(address);
    int new_socket = accept(server_socket, (struct sockaddr *)&address,
        (socklen_t*)&addrlen);
    if (new_socket < 0) {
        perror("accept failed");
        exit(EPITECH_ERROR);
    }
    return new_socket;
}

#include <sys/time.h>

void update_client_struct(int new_socket, client_t *clients,
    server_params_t *server_params)
{
    int i = find_empty_slot(clients);
    if (i != -1) {
        clients[i].socket = new_socket;
        clients[i].is_connected = 1;
        send_response(clients[i].socket, "WELCOME\n");
        char buffer[BUFFER_SIZE];
        ssize_t bytes_read = read_method(new_socket, buffer);
        size_t len = strlen(buffer);
        buffer[len - 1] = (buffer[len - 1] == '\n') ? '\0' : buffer[len - 1];
        if (strcmp(buffer, "GRAPHIC") == 0)
            clients[i].is_graphical = 1;
        clients[i].team_name =
            clients[i].is_graphical == 0 ? msprintf("%s", buffer) : NULL;
        
        struct timeval tv;
        gettimeofday(&tv, NULL);
        long long current_time_in_milliseconds = tv.tv_sec * 1000LL + tv.tv_usec / 1000LL;

        clients[i].food_losing_timer = current_time_in_milliseconds
            + 126000LL / server_params->frequency;
        if (clients[i].is_graphical == 0) {
            if (get_connect_nbr(clients, &clients[i]) <= 0) {
                clients[i].is_connected = 0;
                send_response(clients[i].socket, "ko\n");
                return;
            }
        }
        send_info_loggin(clients[i].socket, &clients[i], server_params);
        send_notification_player_loggin(clients, &clients[i], server_params);
    }
}


void setup_readfds(int server_socket, fd_set *readfds)
{
    FD_ZERO(readfds);
    FD_SET(server_socket, readfds);
}

void wait_for_connections(int server_socket, client_t *clients,
    struct sockaddr_in address, server_params_t *serv_params)
{
    int new_socket = 0;
    fd_set readfds = {0};
    int max_fd = server_socket;
    int activity = 0;
    struct timeval tv;
    tv.tv_sec = 0;
    tv.tv_usec = 100000;
    while (1) {
        setup_readfds(server_socket, &readfds);
        max_fd = set_clients_sockets(clients, &readfds, server_socket);
        activity = select(max_fd + 1, &readfds, NULL, NULL, &tv);
        if ((activity < 0) && (errno != EINTR))
            continue;
        handle_select_errors(activity);
        if (FD_ISSET(server_socket, &readfds)) {
            new_socket = accept_new_connection(server_socket, address);
            update_client_struct(new_socket, clients, serv_params);
        }
        check_client_activity(clients, server_socket, &readfds, serv_params);
    }
}
