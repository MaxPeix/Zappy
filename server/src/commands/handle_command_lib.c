/*
** EPITECH PROJECT, 2023
** lib_handle_command
** File description:
** handle_command_lib
*/

#include "server.h"

// char **add_arg_to_list(char **args, char *command, int command_count)
// {
//     char **temp = realloc(args, sizeof(char *) * (command_count + 1));
//     if (temp == NULL) {
//         free_array(args);
//         return NULL;
//     }
//     args = temp;
//     args[command_count] = strdup(command);
//     if (args[command_count] == NULL) {
//         free_array(args);
//         return NULL;
//     }
//     return args;
// }

// char **get_args_from_buffer(char *buffer)
// {
//     char **args = NULL;
//     char *command = NULL;
//     int command_count = 0;

//     if (!buffer)
//         return NULL;
//     command = strtok(buffer, " \r\n");
//     while (command != NULL) {
//         args = add_arg_to_list(args, command, command_count);
//         if (args == NULL)
//             return NULL;
//         command = strtok(NULL, " \r\n");
//         command_count++;
//     }
//     args[command_count] = NULL;
//     return args;
// }

char **get_args_from_buffer(char *buffer) {
    if (!buffer)
        return NULL;
    
    // Count the number of words
    int word_count = 0;
    for (int i = 0; buffer[i]; i++)
        if (buffer[i] == ' ' || buffer[i] == '\n' || buffer[i] == '\r')
            word_count++;
    
    // Allocate memory for the word array
    char **words = malloc((word_count + 2) * sizeof(char *));
    if (!words)
        return NULL;
    
    // Split the buffering into words
    int word_index = 0;
    char *word = strtok(buffer, " \n\r");
    while (word) {
        words[word_index] = strdup(word);
        if (!words[word_index]) {  // Check for allocation error
            for (int i = 0; i < word_index; i++)
                free(words[i]);
            free(words);
            return NULL;
        }
        word = strtok(NULL, " \n\r");
        word_index++;
    }
    words[word_index] = NULL;  // Null-terminate the word array

    return words;
}


void free_array(char **array)
{
    if (!array)
        return;
    for (int i = 0; array[i]; i++)
        free(array[i]);
    free(array);
}
