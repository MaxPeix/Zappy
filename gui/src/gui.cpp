/*
** EPITECH PROJECT, 2023
** Zappy GUI
** File description:
** gui.cpp
*/

#include "gui.hpp"

GUI::GUI(int port, std::string machine)
{
    this->port = port;
    this->machine = machine;
}

GUI::~GUI()
{
}

void GUI::init_game()
{
    this->window.create(sf::VideoMode(1920, 1080), "Trantor");
    this->window.setFramerateLimit(60);
    this->assets = Assets();
    this->assets.init_assets(this->height, this->width);
}

void GUI::draw_game()
{
    window.draw(this->assets.leftrectangle1);
    window.draw(this->assets.leftrectangle2);
    window.draw(this->assets.leftrectangle3);
    window.draw(this->assets.closeButtonSprite);
    window.draw(this->assets.optionsButtonSprite);
    window.draw(this->assets.text_tna);
    window.draw(this->assets.text_chat);
    window.draw(this->assets.text_info);
    for(int i = 0; i < this->width; i++) {
        for(int j = 0; j < this->height; j++) {
            this->assets.rectangle.setPosition(i * this->assets.box_size + this->assets.rectangle_width, j * this->assets.box_size);
            if((i + j) % 2 == 0)
                this->assets.rectangle.setFillColor(sf::Color::Black);
            else
                this->assets.rectangle.setFillColor(sf::Color::White);
            window.draw(this->assets.rectangle);
        }
    }
}

void GUI::game_loop()
{
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    if (this->assets.closeButtonSprite.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        window.close();
                    }
                    if (this->assets.optionsButtonSprite.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        std::cout << "Options button clicked\n";
                    }
                }
            }
        }
        window.clear();
        draw_game();
        window.display();
    }
}

void GUI::draw_cmd(sf::RenderWindow window, std::string cmd)
{
    window.display();
    if (cmd.compare("msz") == 0)
        return;
    if (cmd.compare("bct") == 0)
        return;
    if (cmd.compare("tna") == 0)
        return;
    if (cmd.compare("pnw") == 0)
        return;
    if (cmd.compare("ppo") == 0)
        return;
    if (cmd.compare("plv") == 0)
        return;
    if (cmd.compare("pin") == 0)
        return;
    if (cmd.compare("pex") == 0)
        return;
    if (cmd.compare("pbc") == 0)
        return;
    if (cmd.compare("pic") == 0)
        return;
    if (cmd.compare("pie") == 0)
        return;
    if (cmd.compare("pfk") == 0)
        return;
    if (cmd.compare("pdr") == 0)
        return;
    if (cmd.compare("pgt") == 0)
        return;
    if (cmd.compare("pdi") == 0)
        return;
    if (cmd.compare("enw") == 0)
        return;
    if (cmd.compare("ebo") == 0)
        return;
    if (cmd.compare("edi") == 0)
        return;
    if (cmd.compare("sgt") == 0)
        return;
    if (cmd.compare("sst") == 0)
        return;
    if (cmd.compare("seg") == 0)
        return;
    if (cmd.compare("smg") == 0)
        return;
    if (cmd.compare("suc") == 0)
        return;
    if (cmd.compare("sbp") == 0)
        return;
    else
        return;
    return;
}

std::string GUI::ask_server(std::string cmd)
{
    std::string response;
    std::cout << cmd;
    return response;
}

int GUI::connectToServer()
{
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        std::cerr << "Failed to create socket." << std::endl;
        return 1;
    }

    std::string serverIP;
    if (this->machine == "localhost")
        serverIP = "127.0.0.1";
    int serverPort = this->port;

    struct sockaddr_in serverAddress{};
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = inet_addr(serverIP.c_str());
    serverAddress.sin_port = htons(serverPort);

    if (connect(clientSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) == -1) {
        std::cerr << "Failed to connect to the server." << std::endl;
        close(clientSocket);
        return 1;
    }

    const char *command = "GRAPHIC\n";
    if (send(clientSocket, command, strlen(command), 0) == -1) {
        std::cerr << "Failed to send command to the server." << std::endl;
        close(clientSocket);
        return 1;
    }

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
    char *line = strtok(buffer, "\n");
    line = strtok(buffer1, "\n");
    while (line != nullptr) {
        if (sscanf(line, "msz %d %d", &x, &y) == 2) {
            std::cout << "Received X: " << x << std::endl;
            std::cout << "Received Y: " << y << std::endl;
            break;
        }
        line = strtok(nullptr, "\n");
    }

    if (line == nullptr)
        std::cerr << "Failed to parse server response." << std::endl;
    this->width = x;
    this->height = y;
    return 0;
}
