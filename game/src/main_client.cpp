#include "../include/library.h"
#include "../include/game.h"
#include "../include/textbox.h"

void game(sf::RenderWindow& window, std::string ip)
{
    //std::cout << ip << std::endl;
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
                    if (event.key.code == sf::Keyboard::Escape)
                        isGame = false;
                    else if (event.key.code == sf::Keyboard::Q)
                        window.close();
                    else if (event.key.code == sf::Keyboard::Space || event.key.code == sf::Keyboard::P) {
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

bool enter_ip(sf::RenderWindow& window)
{
    sf::Vector2f windowsize = sf::Vector2f(window.getSize());
    bool isEnter = true;
    #ifdef __MACH__
        std::string path = "/Users/stassidelnikov/aerohockey-game";
    #else
        std::string path = std::experimental::filesystem::current_path().string();
    #endif

    sf::Font font;
    std::string fontpath = path + "/game/images/arial.ttf";
    font.loadFromFile(fontpath);
    sf::Text suggestion;
    suggestion.setFont(font);
    suggestion.setFillColor(sf::Color::Black);
    suggestion.setStyle(sf::Text::Bold);
    suggestion.setCharacterSize(60);
    suggestion.setString("Enter server ip");
    suggestion.setOrigin(suggestion.getLocalBounds().width / 2, suggestion.getLocalBounds().height);
    float v_padding  = suggestion.getLocalBounds().height;
    //float h_padding = 0; 
    suggestion.setPosition(windowsize.x / 2, windowsize.y / 2 - v_padding);
    TextBox textbox(suggestion);

    while ((window.isOpen()) && isEnter)
    {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch(event.type) {
                case sf::Event::Closed:
                    std::cout << "Closing window." << std::endl;
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                    if (event.key.code == sf::Keyboard::Escape)
                        isEnter = false;
                    break;
                case sf::Event::TextEntered:
                    switch ( event.text.unicode ) {
                        case 0xD: //Return
                        game(window, textbox.get_text());
                        break ;
                        default:
                        textbox.update(event);
                    }
                    
            }
        }

        window.clear(sf::Color(129, 181, 221));
        window.draw(suggestion);
        textbox.draw(window);
		window.display();
    }
    return true;
}

bool menu(sf::RenderWindow& window)
{
    sf::Vector2f windowsize = sf::Vector2f(window.getSize());
    #ifdef __MACH__
        std::string path = "/Users/stassidelnikov/aerohockey-game";
    #else
        std::string path = std::experimental::filesystem::current_path().string();
    #endif

    int buttons_count = 2;
    float padding = 100;
    sf::Image buttonImage;
    buttonImage.loadFromFile(path + "/game/images/buttons.png");
    buttonImage.createMaskFromColor(sf::Color::White);
    sf::Texture buttonTexture;
    buttonTexture.loadFromImage(buttonImage);
    sf::Sprite menubutton(buttonTexture), exitbutton(buttonTexture);

    int height = static_cast<unsigned int>(buttonTexture.getSize().y / buttons_count);
    int width = buttonTexture.getSize().x;
    menubutton.setTextureRect({0, 0, width, height});
    menubutton.setOrigin(width / 2, height / 2);
    menubutton.setPosition({windowsize.x / 2, windowsize.y / 2 - padding});
    exitbutton.setTextureRect({0, height * 1, width, height});
    exitbutton.setOrigin(width / 2, height / 2);
    exitbutton.setPosition({windowsize.x / 2, windowsize.y / 2 + padding});
    sf::FloatRect menubutton_bounds = menubutton.getGlobalBounds();
    sf::FloatRect exitbutton_bounds = exitbutton.getGlobalBounds();

    bool isMenu = true;
    int menuNum = 0;
	while ((isMenu) && (window.isOpen()))
	{
        sf::Event event;
        while (window.pollEvent(event)) {

            switch(event.type) {
                case sf::Event::Closed:
                    std::cout << "Closing window." << std::endl;
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                    std::cout << "Key pressed." << std::endl;
                    if (event.key.code == sf::Keyboard::Escape)
                        isMenu = false;
                    else if (event.key.code == sf::Keyboard::Q)
                        window.close();
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
            std::cout << "button pressed " << menuNum << std::endl;
			if (menuNum == 1) { 
                enter_ip(window);
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