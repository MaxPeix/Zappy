/*
** EPITECH PROJECT, 2023
** handle_error
** File description:
** handle_error
*/

#include "server.h"

void handle_select_errors(int activity)
{
    if ((activity < 0) && (errno != EINTR))
        printf("select error");
}

int check_errors(int argc, char **argv)
{
    if (!argv || !argv[1])
        return EPITECH_ERROR;

    char *error_message = "USAGE: ./zappy port\n\tport is the port \
        number on which the server socket listens\n";

    if (argc == 1 || strcmp(argv[1], "-help") == 0) {
        printf("%s", error_message);
        return 1;
    }

    if (argc != 2)
        return EPITECH_ERROR;
    if (atoi(argv[1]) == 0)
        return EPITECH_ERROR;
    return 0;
}
