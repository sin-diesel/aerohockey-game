#pragma once
#include "../include/library.h"
#include "../include/game.h"
#include "../include/textbox.h"
#include <thread>
class Interface {

    private:
    Game aerohockey;
    sf::Color menu_color;
    sf::Color game_color;
    sf::RenderWindow window;
    std::string path;
    sf::Font font;
    bool start_game(sf::IpAddress server_addr, int choice);
    bool enter_settings();
    void settings_loop(sf::Text suggestion, sf::Text fail, sf::Text suggestion_mode, sf::Sprite mouse_button, sf::Sprite keyboard_button, sf::Text fail_choice);
    void menu_loop(sf::Sprite menubutton, sf::Sprite exitbutton);

    public:
    Interface() = default;
    Interface(unsigned int width, unsigned int height);
    bool start_menu();
    void close_window();
};
