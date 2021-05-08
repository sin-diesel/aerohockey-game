#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>

#include "../include/puck.h"
#include "../include/putter.h"
#include "../include/scoreboard.h"

class Game {
    private:

        Puck puck;
        Putter leftputter;
        Putter rightputter;
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
};