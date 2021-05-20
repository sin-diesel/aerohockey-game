#include "../include/interface.h"
#include <filesystem>
#include <iostream>
#include <limits.h>

Interface::Interface(unsigned int width_, unsigned int height_) : 
    window(sf::VideoMode(width_, height_), "aerohockey-game", sf::Style::Default),
    menu_color(sf::Color(129, 181, 221)),
    game_color(sf::Color(0, 49, 83, 0))
    {
        #ifdef __MACH__
        char buf[PATH_MAX];
        getcwd(buf, PATH_MAX);
        path = std::string(buf); //"/Users/stassidelnikov/aerohockey-game";
        #else
        path = std::filesystem::current_path();
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
    std::vector<int> emptykey(4,-1);
    std::vector<int> key(4, -1);
    while (isGame) {
        sf::Event event;
        sf::Packet packet;
        key = emptykey;
        while (window.pollEvent(event)) {
            switch(event.type) {

                case sf::Event::Closed:
                    std::cout << "Closing window." << std::endl;
                    window.close();
                    break;

                case sf::Event::KeyPressed:
                    if (event.key.code == sf::Keyboard::Escape)
                        isGame = false;
                    else if (event.key.code == sf::Keyboard::Q)
                        window.close();
                    else if (event.key.code == sf::Keyboard::Space || event.key.code == sf::Keyboard::P)
                        pause_flag = (pause_flag == 0) ? 1 : 0;
                    else if (aerohockey.get_type_control()) {
                        if (event.key.code == sf::Keyboard::W)
                            key[0] = sf::Keyboard::W;
                        else if (event.key.code == sf::Keyboard::A)
                            key[1] = sf::Keyboard::A;
                        else if (event.key.code == sf::Keyboard::S)
                            key[2] = sf::Keyboard::S;
                        else if (event.key.code == sf::Keyboard::D)
                            key[3] = sf::Keyboard::D;
                    }
                    break;
                // case sf::Event::GainedFocus:
                //     mouse_pos = sf::Mouse::getPosition(window);
                //     break;
            }
        }
        if (aerohockey.get_type_control() && key != emptykey) {
            packet << key[0] << key[1] << key[2] << key[3];
            aerohockey.send_key(packet);
        }

        if (!pause_flag){
            clock.restart();
            aerohockey.play(window);
            window.clear(game_color);
            aerohockey.draw_objects(window);
            window.display();
        }
    }
    return true;
}

void Interface::settings_loop(SettingsObjects SO)
{
    sf::IpAddress server_addr;
    TextBox textbox(SO.suggestion_ip);
    bool isEnter = true, correctIP = true, choiceDone = false, correctChoice = true;
    sf::FloatRect mouse_bounds = SO.mouse_button.getGlobalBounds();
    sf::FloatRect keyboard_bounds = SO.keyboard_button.getGlobalBounds();
    int buttonnum = NOCHOICE, choice = NOCHOICE;
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
                        case ENTER:
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
        SO.mouse_button.setColor(sf::Color::White);
        SO.keyboard_button.setColor(sf::Color::White);
        if (choiceDone)
            switch(choice){
                case MOUSE: SO.mouse_button.setColor(sf::Color::Green); break;
                case KEYBOARD: SO.keyboard_button.setColor(sf::Color::Green); break;
            }
        buttonnum = NOCHOICE;
        if (mouse_bounds.contains(sf::Vector2f(sf::Mouse::getPosition(window)))) { SO.mouse_button.setColor(sf::Color::Blue); buttonnum  = MOUSE; }
        if (keyboard_bounds.contains(sf::Vector2f(sf::Mouse::getPosition(window)))) { SO.keyboard_button.setColor(sf::Color::Blue); buttonnum  = KEYBOARD; }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            switch (buttonnum) {
                case MOUSE: choice = MOUSE; choiceDone = true; break;
                case KEYBOARD: choice = KEYBOARD; choiceDone = true; break;
            }

        window.clear(menu_color);
        window.draw(SO.suggestion_ip);
        textbox.draw(window);
        if (!correctIP)
            window.draw(SO.fail_ip);
        window.draw(SO.suggestion_mode);
        if (!correctChoice && !choiceDone)
            window.draw(SO.fail_choice);
        window.draw(SO.mouse_button);
        window.draw(SO.keyboard_button);
		window.display();
    }
}

SettingsObjects::SettingsObjects(sf::Font& font, unsigned int charsize, std::string imgbuttonpath)
{
    suggestion_ip.setFont(font);
    suggestion_ip.setFillColor(sf::Color::Black);
    suggestion_ip.setStyle(sf::Text::Bold);
    suggestion_ip.setCharacterSize(charsize);
    suggestion_ip.setString("Enter server ip");
    suggestion_ip.setOrigin(suggestion_ip.getLocalBounds().width / 2, suggestion_ip.getLocalBounds().height);

    fail_ip.setFont(font);
    fail_ip.setFillColor(sf::Color::Black);
    fail_ip.setStyle(sf::Text::Bold);
    fail_ip.setCharacterSize(charsize);
    fail_ip.setString("Error: Invalid IP");
    fail_ip.setOrigin(0, fail_ip.getLocalBounds().height);

    suggestion_mode.setFont(font);
    suggestion_mode.setFillColor(sf::Color::Black);
    suggestion_mode.setStyle(sf::Text::Bold);
    suggestion_mode.setCharacterSize(charsize);
    suggestion_mode.setString("Gaming mode");
    suggestion_mode.setOrigin(suggestion_mode.getLocalBounds().width / 2, suggestion_mode.getLocalBounds().height);

    buttonImage.loadFromFile(imgbuttonpath); buttonImage.createMaskFromColor(sf::Color::White);
    buttonTexture.loadFromImage(buttonImage);
    mouse_button.setTexture(buttonTexture); keyboard_button.setTexture(buttonTexture);
    int height = static_cast<unsigned int>(buttonTexture.getSize().y / 2);
    int width = buttonTexture.getSize().x;
    mouse_button.setTextureRect({0, height * 0, width, height}); keyboard_button.setTextureRect({0, height * 1, width, height});
    mouse_button.setOrigin(width / 2, height / 2); keyboard_button.setOrigin(width / 2, height / 2);

    fail_choice.setFont(font);
    fail_choice.setFillColor(sf::Color::Black);
    fail_choice.setStyle(sf::Text::Bold);
    fail_choice.setCharacterSize(charsize);
    fail_choice.setString("Error: make a choice");
    fail_choice.setOrigin(0, fail_choice.getLocalBounds().height);
}

bool Interface::enter_settings()
{
    sf::Vector2f windowsize = sf::Vector2f(window.getSize());
    SettingsObjects SO(font, 60, path + "/game/images/mouse_keyboard.png");

    //text suggestion to enter ip
    float v_padding  = SO.suggestion_ip.getLocalBounds().height * 3;
    SO.suggestion_ip.setPosition(windowsize.x / 2, windowsize.y / 2 - v_padding);
 
    //text fail if invalid ip
    SO.fail_ip.setPosition(SO.suggestion_ip.getGlobalBounds().left + SO.suggestion_ip.getGlobalBounds().width, SO.suggestion_ip.getPosition().y + SO.suggestion_ip.getLocalBounds().height);

    //text suggestion to make a choice of mode playing
    SO.suggestion_mode.setPosition(windowsize.x / 2, SO.fail_ip.getPosition().y + SO.fail_ip.getLocalBounds().height * 2);

    int buttons_count = 2; //buttons of making mode choice
    float h_padding = 0.6 * SO.mouse_button.getLocalBounds().width; 
    SO.mouse_button.setPosition({SO.suggestion_mode.getPosition().x - h_padding, SO.suggestion_mode.getPosition().y + SO.suggestion_mode.getLocalBounds().height});
    SO.keyboard_button.setPosition({SO.suggestion_mode.getPosition().x + h_padding, SO.suggestion_mode.getPosition().y + SO.suggestion_mode.getLocalBounds().height});

    //text fail if choice hadn't made
    SO.fail_choice.setPosition(SO.keyboard_button.getGlobalBounds().left + SO.keyboard_button.getGlobalBounds().width, SO.suggestion_mode.getPosition().y + SO.suggestion_mode.getLocalBounds().height);

    settings_loop(SO);
    
    return true;
}

void Interface::menu_loop(sf::Sprite menubutton, sf::Sprite exitbutton)
{
    sf::FloatRect menubutton_bounds = menubutton.getGlobalBounds();
    sf::FloatRect exitbutton_bounds = exitbutton.getGlobalBounds();
    bool isMenu = true;
    int menuNum = NOCHOICE;
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
		menuNum = NOCHOICE;
		if (menubutton_bounds.contains(sf::Vector2f(sf::Mouse::getPosition(window)))) { menubutton.setColor(sf::Color::Blue); menuNum = PLAY; }
        if (exitbutton_bounds.contains(sf::Vector2f(sf::Mouse::getPosition(window)))) { exitbutton.setColor(sf::Color::Blue); menuNum = QUIT; }
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            switch (menuNum) {
                case PLAY: enter_settings(); break;
                case QUIT: isMenu = false; break;
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