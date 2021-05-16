#pragma once
#include "../include/library.h"
#include "../include/game.h"
#include "../include/textbox.h"

class Interface {

    private:
    sf::RenderWindow window;
    std::string path;
    bool start_game(std::string ip_addr);
    bool enter_settings();

    public:
    Interface();
    bool start_menu();
    void close_window();
};
