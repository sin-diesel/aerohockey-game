#pragma once
#include "library.h"
#include "puck.h"
#include "scoreboard.h"

class Game {
    private:

        Puck puck;
        Striker striker1;
        Striker striker2;
        Scoreboard scoreboard;
        sf::Time network_update_time = sf::milliseconds(100);

    public:

        Game();
        // virtual destructor in case we are going to use inheritance
        virtual ~Game();

        // this is to be server to compute changes in window
        void update();
        // this is to be used by client to draw stuff
        void render();

        void start_position();

        void play();

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