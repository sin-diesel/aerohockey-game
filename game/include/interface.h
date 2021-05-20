#pragma once
#include "../include/library.h"
#include "../include/game.h"
#include "../include/textbox.h"
#include <thread>
#define ENTER 0xD
enum {
    NOCHOICE = 0,
    MOUSE = 1,
    KEYBOARD = 2,
    PLAY = 3, 
    QUIT = 4
};

enum {
    DEFAULT_WIDTH = 1920,
    DEFAULT_HEIGHT = 1080
};

class SettingsObjects {
    private: 
    sf::Image buttonImage;
    sf::Texture buttonTexture;

    public:
    SettingsObjects() = default;
    SettingsObjects(sf::Font& font, unsigned int charsize, std::string imgbuttonpath);
    sf::Text suggestion_ip; 
    sf::Text fail_ip; 
    sf::Text suggestion_mode;
    sf::Sprite mouse_button;
    sf::Sprite keyboard_button;
    sf::Text fail_choice;
};

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
    void settings_loop(SettingsObjects SO);
    void menu_loop(sf::Sprite menubutton, sf::Sprite exitbutton);
    float factorX;
    float factorY; 

    public:
    Interface() = default;
    Interface(unsigned int width, unsigned int height);
    bool start_menu();
    void close_window();
};
