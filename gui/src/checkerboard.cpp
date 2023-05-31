/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Draw checkerboard
*/

#include "gui.hpp"

void draw_checkerboard(int x, int y)
{
    int taille_case = 50;

    sf::RenderWindow window(sf::VideoMode(taille_case * x, taille_case * y), "Trantor");
    sf::RectangleShape rectangle(sf::Vector2f(taille_case, taille_case));

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        for(int i = 0; i < x; i++) {
            for(int j = 0; j < y; j++) {
                rectangle.setPosition(i * taille_case, j * taille_case);
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
