#pragma once
#include "library.h"
#include "dynamic.h"
#include "scoreboard.h"
#include <unistd.h>
#include <experimental/filesystem>
class Game {
    private:

        ClientDynamicObject puck;
        ClientDynamicObject striker1, striker2;
    
    public:
    const std::string path;
        Scoreboard scoreboard;

        Game() = default;
        Game(sf::Vector2u windowsize);
        // virtual destructor in case we are going to use inheritance
        virtual ~Game();

        // this is to be server to compute changes in window
        void update();
        // this is to be used by client to draw stuff
        void render();

        void play(sf::RenderWindow& window);

        void draw_objects(sf::RenderWindow& window);
};