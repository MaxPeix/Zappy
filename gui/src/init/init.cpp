/*
** EPITECH PROJECT, 2023
** Zappy GUI
** File description:
** Initialisation of map
*/

#include "gui.hpp"

int connectToServer(int port, std::string machine)
{
    // Create a socket
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        std::cerr << "Failed to create socket." << std::endl;
        return 1;
    }

    // Server address and port
    std::string serverIP;  // Replace with the server's IP address
    if (machine == "localhost")
        serverIP = "127.0.0.1";
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
    char buffer1[BUFFER_SIZE];
    memset(buffer1, 0, BUFFER_SIZE);
    if (recv(clientSocket, buffer1, BUFFER_SIZE, 0) == -1) {
        std::cerr << "Failed to receive data from the server." << std::endl;
        close(clientSocket);
        return 1;
    }

    int x, y;
    char *line = strtok(buffer, "\n");  // Split the buffer into lines
    line = strtok(buffer1, "\n");
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

    draw_checkerboard(x, y);

    // Close the socket
    close(clientSocket);

    return 0;
}