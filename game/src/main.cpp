#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>

#include <iostream>

#include "../include/game.h"

int main() {

    // window
    sf::RenderWindow window(sf::VideoMode(800, 600), "aerohockey-game", sf::Style::Default);

    Game aerohockey;

    Game aerohockey;

    // game loop
    while (window.isOpen()) {

        // event polling

        sf::Event event;
        while (window.pollEvent(event)) {

            switch(event.type) {

                case sf::Event::Closed:
                    std::cout << "Closing window." << std::endl;
                    window.close();
                    break;

                case sf::Event::KeyPressed:
                    std::cout << "Key pressed." << std::endl;
                    if (event.key.code == sf::Keyboard::Escape) {
                        window.close();
                    }
                    break;
            }
        }

        aerohockey.play();

        aerohockey.draw_objects(window);

        window.display();
    }


    return 0;
}