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
    if (argc != 2)
        return EPITECH_ERROR;
    if (atoi(argv[1]) == 0)
        return EPITECH_ERROR;
    return 0;
}
