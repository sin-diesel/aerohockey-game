#include "../include/interface.h"

Interface::Interface(unsigned int width_, unsigned int height_) : 
    window(sf::VideoMode(width_, height_), "aerohockey-game", sf::Style::Default),
    menu_color(sf::Color(129, 181, 221)),
    game_color(sf::Color(0, 49, 83, 0))
    {
        #ifdef __MACH__
        path = "/Users/stassidelnikov/aerohockey-game";
        #else
        path = std::experimental::filesystem::current_path().string();
        #endif

        std::string fontpath = path + "/game/images/arial.ttf";
        font.loadFromFile(fontpath);
    }

bool Interface::start_game(sf::IpAddress server_addr)
{
    Game aerohockey(window.getSize(), server_addr, path);
    std::cout << "aerohockey number is " << aerohockey.get_number() << std::endl;
    sf::Clock clock;
    sf::Time elapsed;
    int pause_flag = 0;
    bool isGame = true;
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
            window.clear(game_color);
            aerohockey.draw_objects(window);
            window.display();
        }
    }
    return true;
}

void Interface::settings_loop(sf::Text suggestion, sf::Text fail)
{
    sf::IpAddress server_addr;
    TextBox textbox(suggestion);
    bool isEnter = true, correctIP = true;
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
                        if ((server_addr = sf::IpAddress(textbox.get_text())) == sf::IpAddress::None) {
                            std::cerr << "Error converting to valid IP address" << std::endl;
                            correctIP = false;
                            break;
                        }
                        start_game(server_addr);
                        break ;
                        default:
                        textbox.update(event);
                        correctIP = true;
                    }
                    
            }
        }

        window.clear(menu_color);
        window.draw(suggestion);
        textbox.draw(window);
        if (!correctIP)
            window.draw(fail);
		window.display();
    }
}

bool Interface::enter_settings()
{
    sf::Vector2f windowsize = sf::Vector2f(window.getSize());
    sf::Text suggestion;
    suggestion.setFont(font);
    suggestion.setFillColor(sf::Color::Black);
    suggestion.setStyle(sf::Text::Bold);
    suggestion.setCharacterSize(60);
    suggestion.setString("Enter server ip");
    suggestion.setOrigin(suggestion.getLocalBounds().width / 2, suggestion.getLocalBounds().height);
    float v_padding  = suggestion.getLocalBounds().height;
    suggestion.setPosition(windowsize.x / 2, windowsize.y / 2 - v_padding);
 
    sf::Text fail;
    fail.setFont(font);
    fail.setFillColor(sf::Color::Black);
    fail.setStyle(sf::Text::Bold);
    fail.setCharacterSize(60);
    fail.setString("Invalid IP");
    fail.setOrigin(0, fail.getLocalBounds().height);
    fail.setPosition(suggestion.getGlobalBounds().left + suggestion.getGlobalBounds().width, windowsize.y / 2);
    settings_loop(suggestion, fail);
    
    return true;
}

void Interface::menu_loop(sf::Sprite menubutton, sf::Sprite exitbutton)
{
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

        menubutton.setColor(sf::Color::White);
        exitbutton.setColor(sf::Color::White);
		
		menuNum = 0;
		if (menubutton_bounds.contains(sf::Vector2f(sf::Mouse::getPosition(window)))) { menubutton.setColor(sf::Color::Blue); menuNum = 1; }
        if (exitbutton_bounds.contains(sf::Vector2f(sf::Mouse::getPosition(window)))) { exitbutton.setColor(sf::Color::Blue); menuNum = 2; }
 
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
            std::cout << "button pressed " << menuNum << std::endl;
			if (menuNum == 1) { 
                enter_settings();
            } 
			if (menuNum == 2)  { 
                isMenu = false; 
                std::cout << "Closing menu" << std::endl;
            }
 
		}
        
        window.clear(menu_color);
		window.draw(menubutton);
		window.draw(exitbutton);
		window.display();
	}
}

bool Interface::start_menu()
{
    sf::Vector2f windowsize = sf::Vector2f(window.getSize());

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

    menu_loop(menubutton, exitbutton);
    return true;
}

void Interface::close_window()
{
    window.close();
}