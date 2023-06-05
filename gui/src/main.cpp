/*
** EPITECH PROJECT, 2023
** Zappy GUI
** File description:
** main for gui client
*/

#include "gui.hpp"

int parseArguments(int ac, char **av, int& port, std::string& machine)
{
    if (ac != 5) {
        std::cout << "USAGE: " << av[0] << " -p port -h machine" << std::endl;
        return ERROR;
    }

    for (int i = 1; i < ac; i += 2) {
        if (strcmp(av[i], "-p") == 0) {
            try {
                port = std::stoi(av[i + 1]);
            } catch (const std::exception& e) {
                std::cout << "Invalid port: " << av[i + 1] << std::endl;
                return ERROR;
            }
        } else if (strcmp(av[i], "-h") == 0) {
            machine = av[i + 1];
        } else {
            std::cout << "Invalid option: " << av[i] << std::endl;
            return ERROR;
        }
    }

    return SUCCESS;
}

int main(int ac, char **av)
{
    int port = 0;
    std::string machine = "localhost";

    if (parseArguments(ac, av, port, machine) != 0) {
        return ERROR;
    }
    GUI gui(port, machine);
    gui.connectToServer();
    gui.draw_game();
    return SUCCESS;
}
