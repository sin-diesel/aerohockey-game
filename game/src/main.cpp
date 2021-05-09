#include "../include/library.h"
#include "../include/game.h"

int main() {

    // window
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "aerohockey-game", sf::Style::Default);
    Game aerohockey;

    sf::Texture background_image;
    sf::Sprite background;
    background_image.loadFromFile("/home/sergey/aerohockey-game/game/images/background.png");
    background.setTexture(background_image);

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
        

        aerohockey.play();

        window.clear();
        window.draw(background);
        aerohockey.draw_objects(window);
        window.display();
    }


    return 0;
}