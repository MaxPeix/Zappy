/*
** EPITECH PROJECT, 2023
** lib_client
** File description:
** lib
*/

#include "server.h"

void send_response(int socket, char *message)
{
    write(socket, message, strlen(message));
    printf("Sent: %s", message);
    fflush(stdout);
}

void read_method(int socket, char *buffer)
{
    memset(buffer, 0, BUFFER_SIZE);
    read(socket, buffer, BUFFER_SIZE);
    printf("Message reçu: %s\n", buffer);
}
