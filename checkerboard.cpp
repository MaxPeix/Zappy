#include <SFML/Graphics.hpp>

void draw_checkerboard()
{
    int taille_case = 50;
    int nb_cases = 8;
    
    sf::RenderWindow window(sf::VideoMode(taille_case * nb_cases, taille_case * nb_cases), "Trantor");
    sf::RectangleShape rectangle(sf::Vector2f(taille_case, taille_case));
    
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        for(int i = 0; i < nb_cases; i++) {
            for(int j = 0; j  < nb_cases; j++) {
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

int main()
{
    draw_checkerboard();
    return 0;
}
