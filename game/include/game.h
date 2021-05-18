#pragma once
#include "library.h"
#include "dynamic.h"
#include "scoreboard.h"
#include "client.h"

class Game {
    private:
        sf::Time network_update_time = sf::milliseconds(PING);
        int number;
        std::string path;
        Client client;
        ClientDynamicObject puck, striker1, striker2;
        Scoreboard scoreboard;
        sf::Image field_image;
        sf::Texture field_texture;
        sf::Sprite field;
    public:
        
        Game() = default;
        Game(sf::Vector2u windowsize, sf::IpAddress& server_addr, std::string path_);
        void sending_mouse_pos(sf::Window& window);
        int get_number();
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
