/*
** EPITECH PROJECT, 2023
** broadcast command
** File description:
** broadcast_command
*/

#include "server.h"

char *build_message(char **args)
{
    char *message = NULL;
    for (int i = 1; args[i] != NULL; i++) {
        if (message == NULL) {
            message = strdup(args[i]);
        } else {
            char *new_message = NULL;
            new_message = msprintf("%s %s", message, args[i]);
            free(message);
            message = new_message;
        }
    }
    return message;
}

void send_to_graphical_clients(client_t *clients, char *output)
{
    for (int i = 0; i < MAX_CLIENTS; i++)
        if (clients[i].is_graphical == 1)
            send_response(clients[i].socket, output);
}

void handle_broadcast_command(client_t *clients,
    client_t *client, char **args)
{
    if (!args)
        return;
    if (args[0] == NULL)
        return;
    if (strcasecmp(args[0], "BROADCAST") == 0) {
        if (args[1] == NULL) {
            send_response(client->socket, "ko\n");
            return;
        }
        char *message = build_message(args);
        if (!message) {
            printf("Error: Could not allocate memory for message\n");
            return;
        }
        char *output = msprintf("pbc %d %s\n", client->id, message);
        free(message);
        if (!output) {
            printf("Error: Could not allocate memory for output string\n");
            return;
        }
        send_to_graphical_clients(clients, output);
        send_response(client->socket, "ok\n");
        free(output);
    }
}
