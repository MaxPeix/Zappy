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

ssize_t read_method(int socket, char *buffer)
{
    memset(buffer, 0, BUFFER_SIZE);
    ssize_t bytes_read = read(socket, buffer, BUFFER_SIZE - 1);
    if (bytes_read < 0) {
        perror("read");
        return -1;
    }
    buffer[bytes_read] = '\0';
    printf("Message reçu: %s\n", buffer);
    return bytes_read;
}
