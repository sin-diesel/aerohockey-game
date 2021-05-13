#include "../include/library.h"
#include "../include/game.h"

void game(sf::RenderWindow& window)
{
    sf::Clock clock;
    sf::Time elapsed;
    int pause_flag = 0;
    bool isGame = true;

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

    while (isGame) {
        
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
                        isGame = false;
                    }
                    if (event.key.code == sf::Keyboard::Space || event.key.code == sf::Keyboard::P) {
                        pause_flag = (pause_flag == 0) ? 1 : 0;
                    }
                    break;
                // case sf::Event::GainedFocus:
                //     mouse_pos = sf::Mouse::getPosition(window);
                //     break;
            }
        }

        elapsed = clock.getElapsedTime();
        if ((elapsed > aerohockey.get_update_time()) && (!pause_flag)){
            clock.restart();
            aerohockey.play(window);
            window.clear(sf::Color(0, 49, 83, 0));
            window.draw(background);
            aerohockey.draw_objects(window);
            window.display();
        }
    }
}

bool menu(sf::RenderWindow& window)
{
    #ifdef __MACH__
        std::string path = "/Users/stassidelnikov/aerohockey-game";
    #else
        std::string path = std::experimental::filesystem::current_path().string();
    #endif

    sf::Texture buttonTexture;
    buttonTexture.loadFromFile(path + "/game/images/button.png");
    sf::Sprite menubutton(buttonTexture), exitbutton(buttonTexture);
    bool isMenu = true;
    int menuNum = 0;
	menubutton.setPosition(100, 30);
    exitbutton.setPosition(100, 330);
    sf::FloatRect menubutton_bounds = menubutton.getGlobalBounds();
    sf::FloatRect exitbutton_bounds = exitbutton.getGlobalBounds();

	while ((isMenu) && (window.isOpen()))
	{
        sf::Event event;
        while (window.pollEvent(event)) {

            switch(event.type) {
                case sf::Event::Closed:
                    std::cout << "Closing window." << std::endl;
                    window.close();
                    break;
            }
        }

        //std::cout << "menu loop" << std::endl;
        menubutton.setColor(sf::Color::White);
        exitbutton.setColor(sf::Color::White);
		
		menuNum = 0;
		if (menubutton_bounds.contains(sf::Vector2f(sf::Mouse::getPosition(window)))) { menubutton.setColor(sf::Color::Blue); menuNum = 1; }
        if (exitbutton_bounds.contains(sf::Vector2f(sf::Mouse::getPosition(window)))) { exitbutton.setColor(sf::Color::Blue); menuNum = 2; }
 
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
            //std::cout << "button pressed " << menuNum << std::endl;
			if (menuNum == 1) { 
                game(window);
            } 
			if (menuNum == 2)  { 
                isMenu = false; 
                std::cout << "Closing menu" << std::endl;
            }
 
		}
        
        window.clear(sf::Color(129, 181, 221));
		window.draw(menubutton);
		window.draw(exitbutton);
		window.display();
	}
    return true;
}

int main() {
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "aerohockey-game", sf::Style::Default);
    menu(window);
    window.close();
    return 0;
}