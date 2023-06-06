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

void GUI::draw_game()
{
    int box_size = 1080 / this->height;
    int width_checkerboard = box_size * this->width;
    int rectangle_width = 1920 - width_checkerboard;
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Trantor");
    sf::RectangleShape rectangle(sf::Vector2f(box_size, box_size));
    sf::Font font;

    if (!font.loadFromFile("assets/Bronten.ttf")) {
        std::cerr << "Failed to load font." << std::endl;
        return;
    }

    sf::Text text1;
    text1.setFont(font);
    text1.setString("Teams name/Player :");
    text1.setCharacterSize(40);
    text1.setFillColor(sf::Color::Black);
    text1.setPosition(250, 10);

    sf::Text text2;
    text2.setFont(font);
    text2.setString("Chat :");
    text2.setCharacterSize(40);
    text2.setFillColor(sf::Color::Black);
    text2.setPosition(350, 1080 / 3 + 10);

    sf::Text text3;
    text3.setFont(font);
    text3.setString("Info :");
    text3.setCharacterSize(40);
    text3.setFillColor(sf::Color::Black);
    text3.setPosition(350, 2 * 1080 / 3 + 10);

    sf::RectangleShape leftRectangle1(sf::Vector2f(rectangle_width, 1080 / 3));
    leftRectangle1.setPosition(0, 0);
    leftRectangle1.setFillColor(sf::Color::Blue);

    sf::RectangleShape leftRectangle2(sf::Vector2f(rectangle_width, 1080 / 3));
    leftRectangle2.setPosition(0, 1080 / 3);
    leftRectangle2.setFillColor(sf::Color::Red);

    sf::RectangleShape leftRectangle3(sf::Vector2f(rectangle_width, 1080 / 3));
    leftRectangle3.setPosition(0, 2 * 1080 / 3);
    leftRectangle3.setFillColor(sf::Color::Green);

    sf::Texture closeButtonTexture;
    if (!closeButtonTexture.loadFromFile("assets/quit-icon.png")) {
        std::cerr << "Failed to load close button texture." << std::endl;
        return;
    }

    sf::Sprite closeButton;
    closeButton.setTexture(closeButtonTexture);
    closeButton.setPosition(10, 10);

    sf::Texture optionsButtonTexture;
    if (!optionsButtonTexture.loadFromFile("assets/options.png")) {
        std::cerr << "Failed to load options button texture." << std::endl;
        return;
    }

    sf::Sprite optionsButton;
    optionsButton.setTexture(optionsButtonTexture);
    optionsButton.setPosition(80, 10);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    if (closeButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        window.close();
                    }
                    if (optionsButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        std::cout << "Options button clicked\n";
                    }
                }
            }
        }
        window.clear();

        window.draw(leftRectangle1);
        window.draw(leftRectangle2);
        window.draw(leftRectangle3);
        window.draw(closeButton);
        window.draw(optionsButton);
        window.draw(text1);
        window.draw(text2);
        window.draw(text3);

        for(int i = 0; i < this->width; i++) {
            for(int j = 0; j < this->height; j++) {
                rectangle.setPosition(i * box_size + rectangle_width, j * box_size);
                if((i + j) % 2 == 0)
                    rectangle.setFillColor(sf::Color::Black);
                else
                    rectangle.setFillColor(sf::Color::White);
                window.draw(rectangle);
            }
        }
        window.display();
    }
}