#include "../include/interface.h"
//#include <unistd.h>
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


bool Interface::start_game(sf::IpAddress server_addr, int choice)
{
    //std::cout << "choice: " << choice << std::endl;
    Game aerohockey(window.getSize(), server_addr, path, choice);
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
                    else if (event.key.code == sf::Keyboard::Space || event.key.code == sf::Keyboard::P)
                        pause_flag = (pause_flag == 0) ? 1 : 0;
                    else if (aerohockey.get_type_control()) {
                        std::cout << "CONTROL KEYBOARD TRIGGERED" << std::endl;
                        if (event.key.code == sf::Keyboard::W) {
                            aerohockey.send_key(sf::Keyboard::W);
                            //sleep(1);
                        }
                        else if (event.key.code == sf::Keyboard::A)
                            aerohockey.send_key(sf::Keyboard::A);
                        else if (event.key.code == sf::Keyboard::S)
                            aerohockey.send_key(sf::Keyboard::S);
                        else if (event.key.code == sf::Keyboard::D)
                            aerohockey.send_key(sf::Keyboard::D);
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

void Interface::settings_loop(sf::Text suggestion_ip, sf::Text fail, sf::Text suggestion_mode, sf::Sprite mouse_button, sf::Sprite keyboard_button, sf::Text fail_choice)
{
    sf::IpAddress server_addr;
    TextBox textbox(suggestion_ip);
    bool isEnter = true, correctIP = true, choiceDone = false, correctChoice = true;
    sf::FloatRect mouse_bounds = mouse_button.getGlobalBounds();
    sf::FloatRect keyboard_bounds = keyboard_button.getGlobalBounds();
    int buttonnum = 0, choice = 0;
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
                        if (!choiceDone){
                            std::cerr << "make a choice" << std::endl;
                            correctChoice = false;
                            break;
                        }
                        start_game(server_addr, choice);
                        break ;
                        default:
                        textbox.update(event);
                        correctIP = true;
                    }
                    
            } 
        }
        mouse_button.setColor(sf::Color::White);
        keyboard_button.setColor(sf::Color::White);

        if (choiceDone)
            switch(choice){
                case 1: mouse_button.setColor(sf::Color::Green); break;
                case 2: keyboard_button.setColor(sf::Color::Green); break;
            }
        buttonnum = 0;
        if (mouse_bounds.contains(sf::Vector2f(sf::Mouse::getPosition(window)))) { mouse_button.setColor(sf::Color::Blue); buttonnum  = 1; }
        if (keyboard_bounds.contains(sf::Vector2f(sf::Mouse::getPosition(window)))) { keyboard_button.setColor(sf::Color::Blue); buttonnum  = 2; }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
            //std::cout << "button pressed " << buttonnum << std::endl;
			if (buttonnum == 1) { 
                choice = 1;
                choiceDone = true;
            } 
			if (buttonnum == 2)  { 
                choice = 2;
                choiceDone = true;
            }
        }
        //if (choice == 2) {
        //    std::cout << "KEYBOARD IS CHOSEN" << std::endl;
        //}
        window.clear(menu_color);
        window.draw(suggestion_ip);
        textbox.draw(window);
        if (!correctIP)
            window.draw(fail);
        window.draw(suggestion_mode);
        if (!correctChoice && !choiceDone)
            window.draw(fail_choice);
        window.draw(mouse_button);
        window.draw(keyboard_button);
		window.display();
    }
}

bool Interface::enter_settings()
{
    sf::Vector2f windowsize = sf::Vector2f(window.getSize());
    sf::Text suggestion_ip;
    suggestion_ip.setFont(font);
    suggestion_ip.setFillColor(sf::Color::Black);
    suggestion_ip.setStyle(sf::Text::Bold);
    suggestion_ip.setCharacterSize(60);
    suggestion_ip.setString("Enter server ip");
    suggestion_ip.setOrigin(suggestion_ip.getLocalBounds().width / 2, suggestion_ip.getLocalBounds().height);
    float v_padding  = suggestion_ip.getLocalBounds().height * 3;
    suggestion_ip.setPosition(windowsize.x / 2, windowsize.y / 2 - v_padding);
 
    sf::Text fail;
    fail.setFont(font);
    fail.setFillColor(sf::Color::Black);
    fail.setStyle(sf::Text::Bold);
    fail.setCharacterSize(60);
    fail.setString("Error: Invalid IP");
    fail.setOrigin(0, fail.getLocalBounds().height);
    fail.setPosition(suggestion_ip.getGlobalBounds().left + suggestion_ip.getGlobalBounds().width, suggestion_ip.getPosition().y + suggestion_ip.getLocalBounds().height);

    sf::Text suggestion_mode;
    suggestion_mode.setFont(font);
    suggestion_mode.setFillColor(sf::Color::Black);
    suggestion_mode.setStyle(sf::Text::Bold);
    suggestion_mode.setCharacterSize(60);
    suggestion_mode.setString("Gaming mode");
    suggestion_mode.setOrigin(suggestion_mode.getLocalBounds().width / 2, suggestion_mode.getLocalBounds().height);
    suggestion_mode.setPosition(windowsize.x / 2, fail.getPosition().y + fail.getLocalBounds().height * 2);

    int buttons_count = 2;
    sf::Image buttonImage;
    buttonImage.loadFromFile(path + "/game/images/mouse_keyboard.png");
    buttonImage.createMaskFromColor(sf::Color::White);
    sf::Texture buttonTexture;
    buttonTexture.loadFromImage(buttonImage);
    sf::Sprite mouse_button(buttonTexture), keyboard_button(buttonTexture);
    int height = static_cast<unsigned int>(buttonTexture.getSize().y / buttons_count);
    int width = buttonTexture.getSize().x;
    float h_padding = 1.2 * (width / 2); 
    mouse_button.setTextureRect({0, 0, width, height});
    mouse_button.setOrigin(width / 2, height / 2);
    mouse_button.setPosition({suggestion_mode.getPosition().x - h_padding, suggestion_mode.getPosition().y + suggestion_mode.getLocalBounds().height});
    keyboard_button.setTextureRect({0, height * 1, width, height});
    keyboard_button.setOrigin(width / 2, height / 2);
    keyboard_button.setPosition({suggestion_mode.getPosition().x + h_padding, suggestion_mode.getPosition().y + suggestion_mode.getLocalBounds().height});

    sf::Text fail_choice;
    fail_choice.setFont(font);
    fail_choice.setFillColor(sf::Color::Black);
    fail_choice.setStyle(sf::Text::Bold);
    fail_choice.setCharacterSize(60);
    fail_choice.setString("Error: make a choice");
    fail_choice.setOrigin(0, fail_choice.getLocalBounds().height);
    fail_choice.setPosition(keyboard_button.getGlobalBounds().left + keyboard_button.getGlobalBounds().width, suggestion_mode.getPosition().y + suggestion_mode.getLocalBounds().height);

    settings_loop(suggestion_ip, fail, suggestion_mode, mouse_button, keyboard_button, fail_choice);
    
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