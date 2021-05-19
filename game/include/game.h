#pragma once
#include "library.h"
#include "dynamic.h"
#include "scoreboard.h"
#include "client.h"

class Game {
    private:
        sf::Time network_update_time = sf::milliseconds(PING);
        int number = 0;
        const bool keyboard_control = false;
        std::string path;
        Client client;
        ClientDynamicObject puck, striker1, striker2;
        Scoreboard scoreboard;
        sf::Image field_image;
        sf::Texture field_texture;
        sf::Sprite field;
    public:
        Game() = default;
        Game(sf::Vector2u windowsize, sf::IpAddress& server_addr, std::string path_0, int choise);
        void sending_mouse_pos(sf::Window& window);
        void send_key(int key);
        int get_number();
        bool get_type_control();
        void set_number(int num);
        void play(sf::RenderWindow& window);
        void draw_objects(sf::RenderWindow& window);
        sf::Time get_update_time();
};


struct NetworkPacket {
    float pos1_x;
    float pos2_x;
    
    float pos1_y;
    float pos2_y;

    float puck_x;
    float puck_y;
};
