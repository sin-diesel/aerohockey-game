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
};