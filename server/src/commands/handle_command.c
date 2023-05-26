/*
** EPITECH PROJECT, 2023
** handle_command
** File description:
** handle_command
*/

#include "server.h"

void handle_command_three(client_t *clients, int index,
    char *command, int found)
{
    if (found == 0)
        send_response(clients[index].socket, "Zappy: Unknown command.\n");
}

void handle_command_two(client_t *clients, int index, char *command,
    int found)
{
    handle_command_three(clients, index, command, found);
}

void handle_command(client_t *clients, int index, char *buffer)
{
    char *command = strtok(buffer, " \r\n");
    int found = 0;

    if (!command || strlen(command) == 0) {
        send_response(clients[index].socket, "Zappy: Unknown command.\n");
        return;
    }
    if (strcasecmp(command, "HELP") == 0) {
        send_response(clients[index].socket, "Zappy: Help message.\n");
        found++;
    }
    if (strcasecmp(buffer, "QUIT") == 0) {
        send_response(clients[index].socket, "Goodbye.\n");
        handle_disconnect(clients, clients[index].socket, index);
        return;
    }
    handle_command_two(clients, index, command, found);
}
