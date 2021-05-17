#pragma once
#include "../include/library.h"
#include "../include/game.h"
#include "../include/textbox.h"

class Interface {

    private:
    Game aerohockey;
    sf::Color menu_color;
    sf::Color game_color;
    sf::RenderWindow window;
    std::string path;
    bool start_game(std::string ip_addr);
    bool enter_settings();
    void game_loop(sf::IpAddress server_addr);
    void settings_loop(sf::Text suggestion);
    void menu_loop(sf::Sprite menubutton, sf::Sprite exitbutton);

    public:
    Interface() = default;
    Interface(unsigned int width, unsigned int height);
    bool start_menu();
    void close_window();
};
