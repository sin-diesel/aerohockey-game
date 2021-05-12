#pragma once
#include "library.h"
#include "dynamic.h"
#include "scoreboard.h"
#include <unistd.h>
#include <experimental/filesystem>
#include <vector>
#define PING 100 //ms


class Game {
    private:
        sf::Time network_update_time = sf::milliseconds(PING);
    public:
        int number;
        std::string path;
        ClientDynamicObject puck, striker1, striker2;
        Scoreboard scoreboard;
        Game() = default;
        Game(sf::Vector2u windowsize, int num);
        // virtual destructor in case we are going to use inheritance
        virtual ~Game();

        // this is to be server to compute changes in window
        void update();
        // this is to be used by client to draw stuff
        void render();

        void play(sf::RenderWindow& window);

        void draw_objects(sf::RenderWindow& window);

        sf::Time get_update_time() {
            return network_update_time;
        }
};


struct NetworkPacket {
    float pos1_x;
    float pos2_x;
    
    float pos1_y;
    float pos2_y;

    float puck_x;
    float puck_y;
};

sf::Packet& operator <<(sf::Packet& packet, const sf::Vector2f& pos);

sf::Packet& operator >>(sf::Packet& packet, sf::Vector2f& pos);

sf::Packet& operator <<(sf::Packet& packet, const sf::Vector2i& pos);

sf::Packet& operator >>(sf::Packet& packet, sf::Vector2i& pos);