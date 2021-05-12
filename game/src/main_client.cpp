#include "../include/library.h"
#include "../include/game.h"

int main() {
    sf::Clock clock;
    sf::Time elapsed;
    int pause_flag = 0;

    // window
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "aerohockey-game", sf::Style::Default);
    Game aerohockey(window.getSize());
    std::cout << "aerohockey number is " << aerohockey.number << std::endl;
    sf::Image background_image;
    sf::Texture background_texture;
    sf::Sprite background;
    #ifdef __MACH__
        std::string path = "/Users/stassidelnikov/aerohockey-game";
    #else
        std::string path = std::experimental::filesystem::current_path().string();
    #endif
    background_image.loadFromFile(path + "/game/images/background.png");
    background_image.createMaskFromColor(sf::Color::White);
    background_texture.loadFromImage(background_image);
    background.setTexture(background_texture);
    background.setOrigin(background_image.getSize().x / 2, 0);
    background.setPosition(window.getSize().x / 2, aerohockey.scoreboard.getSize().y);

    // game loop

    while (window.isOpen()) {
        
        sf::Event event;
        while (window.pollEvent(event)) {

            switch(event.type) {

                case sf::Event::Closed:
                    std::cout << "Closing window." << std::endl;
                    window.close();
                    break;

                case sf::Event::KeyPressed:
                    std::cout << "Key pressed." << std::endl;
                    if (event.key.code == sf::Keyboard::Escape || event.key.code == sf::Keyboard::Q) {
                        window.close();
                    }
                    if (event.key.code == sf::Keyboard::Space || event.key.code == sf::Keyboard::P) {
                        pause_flag = (pause_flag == 0) ? 1 : 0;
                        //pause_flag = 1;
                    }
                    break;
            }
        }

        elapsed = clock.getElapsedTime();
        if ((elapsed > aerohockey.get_update_time()) && (!pause_flag)){
            aerohockey.play(window);
            window.clear(sf::Color(0, 49, 83, 0));
            window.draw(background);
            aerohockey.draw_objects(window);
            window.display();
            clock.restart();
        }
    }

    return 0;
}