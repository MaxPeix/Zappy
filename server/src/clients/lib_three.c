/*
** EPITECH PROJECT, 2023
** lib_three
** File description:
** lib_three
*/

#include "server.h"

int length_of_int(int *array)
{
    int len = 0;
    while (array && array[len] != 0)
        len++;

    return len;
}
