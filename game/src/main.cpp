#include "../include/library.h"
#include "../include/game.h"

int main() {

    // window
    sf::RenderWindow window(sf::VideoMode(800, 600), "aerohockey-game", sf::Style::Default);
    Game aerohockey = Game();

    // game loop
    sf::Vector2i mouse_pos;
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
        mouse_pos = sf::Mouse::getPosition(window);
        // Update

        // Render

        aerohockey.play();

        aerohockey.draw_objects(window);

        window.display();
    }


    return 0;
}