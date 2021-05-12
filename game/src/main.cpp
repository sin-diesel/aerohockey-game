#include "../include/library.h"
#include "../include/game.h"

int main() {

    // window
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "aerohockey-game", sf::Style::Default);
    Game aerohockey = Game(window.getSize());

    sf::Image background_image;
    sf::Texture background_texture;
    sf::Sprite background;
    background_image.loadFromFile("/Users/stassidelnikov/aerohockey-game/game/images/background.png");
    background_image.createMaskFromColor(sf::Color::White);
    background_texture.loadFromImage(background_image);
    background.setTexture(background_texture);
    background.setOrigin(background_image.getSize().x / 2, 0);
    background.setPosition(window.getSize().x / 2, aerohockey.scoreboard.getSize().y);

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
        sf::Vector2f float_mouse_pos(mouse_pos);
        

        aerohockey.play(window);

        window.clear(sf::Color(0, 49, 83, 0));
        window.draw(background);
        aerohockey.draw_objects(window);
        window.display();
    }


    return 0;
}