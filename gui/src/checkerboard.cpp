/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Draw checkerboard
*/

#include "gui.hpp"

void draw_checkerboard(int x, int y)
{
    int box_size = 1080 / y;
    int width_checkerboard = box_size * x;
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

        for(int i = 0; i < x; i++) {
            for(int j = 0; j < y; j++) {
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
