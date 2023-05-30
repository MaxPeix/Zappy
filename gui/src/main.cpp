/*
** EPITECH PROJECT, 2023
** Zappy GUI
** File description:
** main for gui client
*/

#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define SUCCESS 0
#define ERROR 84

const int BUFFER_SIZE = 4096;

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

int connectToServer(int port, std::string machine)
{
    // Create a socket
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        std::cerr << "Failed to create socket." << std::endl;
        return 1;
    }

    // Server address and port
    std::string serverIP = "127.0.0.1";  // Replace with the server's IP address
    int serverPort = port;  // Replace with the server's port number

    // Set up the server address structure
    struct sockaddr_in serverAddress{};
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = inet_addr(serverIP.c_str());
    serverAddress.sin_port = htons(serverPort);

    // Connect to the server
    if (connect(clientSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) == -1) {
        std::cerr << "Failed to connect to the server." << std::endl;
        close(clientSocket);
        return 1;
    }

    // Send the "GRAPHIC" command to the server
    const char *command = "GRAPHIC\n";
    if (send(clientSocket, command, strlen(command), 0) == -1) {
        std::cerr << "Failed to send command to the server." << std::endl;
        close(clientSocket);
        return 1;
    }

    // Receive the server response (X and Y values)
    char buffer[BUFFER_SIZE];
    memset(buffer, 0, BUFFER_SIZE);
    if (recv(clientSocket, buffer, BUFFER_SIZE, 0) == -1) {
        std::cerr << "Failed to receive data from the server." << std::endl;
        close(clientSocket);
        return 1;
    }

    // Parse the received data
    int x, y;
    char *line = strtok(buffer, "\n");  // Split the buffer into lines

    while (line != nullptr) {
        if (sscanf(line, "msz %d %d", &x, &y) == 2) {
            std::cout << "Received X: " << x << std::endl;
            std::cout << "Received Y: " << y << std::endl;
            break;  // Exit the loop if a matching line is found
        }

        line = strtok(nullptr, "\n");  // Get the next line
    }

    if (line == nullptr) {
        std::cerr << "Failed to parse server response." << std::endl;
    }

    std::cout << "Received: " << buffer << std::endl;
    // Close the socket
    close(clientSocket);

    return 0;
}

int main(int ac, char **av)
{
    int port = 0;
    std::string machine = "localhost";

    if (parseArguments(ac, av, port, machine) != 0) {
        return ERROR;
    }
    if (connectToServer(port, machine) != 0) {
        return ERROR;
    }
    return SUCCESS;
}
