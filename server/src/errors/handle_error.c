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

int check_error_params(server_params_t params)
{
    if (params.port < 5) {
        printf("Port is not a valid number (%d)\n", params.port);
        return EPITECH_ERROR;
    }
    return 0;
}

int check_errors(int argc, char **argv, server_params_t params)
{
    if (!argv || !argv[1])
        return EPITECH_ERROR;
    if (argc == 1 || strcmp(argv[1], "-help") == 0) {
        FILE *file = fopen("helper.txt", "r");
        if (file) {
            char buffer[256];
            while (fgets(buffer, sizeof(buffer), file))
                printf("%s", buffer);
            fclose(file);
        } else
            printf("Failed to open helper.txt\n");
        return 1;
    }
    if (check_error_params(params) == EPITECH_ERROR)
        return EPITECH_ERROR;
    return 0;
}
