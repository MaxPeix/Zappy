/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Draw checkerboard
*/

#include "gui.hpp"

void draw_checkerboard(int x, int y)
{
    int taille_case = 1080 / (y + 2);
    int largeur_damier = taille_case * x;
    int largeur_rectangle = 1920 - largeur_damier;

    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Trantor");
    sf::RectangleShape rectangle(sf::Vector2f(taille_case, taille_case));

    sf::RectangleShape topRectangle(sf::Vector2f(1920, taille_case * 1.5));
    topRectangle.setPosition(0, 0);
    topRectangle.setFillColor(sf::Color::Green);

    sf::RectangleShape leftRectangle1(sf::Vector2f(largeur_rectangle, taille_case * y / 2));
    leftRectangle1.setPosition(0, taille_case * 1.5);
    leftRectangle1.setFillColor(sf::Color::Blue);

    sf::RectangleShape leftRectangle2(sf::Vector2f(largeur_rectangle, taille_case * y / 2));
    leftRectangle2.setPosition(0, taille_case * (y / 2 + 1.5));
    leftRectangle2.setFillColor(sf::Color::Red);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();

        window.draw(topRectangle);
        window.draw(leftRectangle1);
        window.draw(leftRectangle2);

        for(int i = 0; i < x; i++) {
            for(int j = 0; j < y; j++) {
                rectangle.setPosition(i * taille_case + largeur_rectangle, j * taille_case + taille_case * 1.5);
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
