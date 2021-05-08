#pragma once
#include "game.h"

class Scoreboard {
    private:


    sf::Sprite sprite;
    bool scored;

    public:
    Scoreboard();
    void update();
    bool goalscored();
    void unscored();
    sf::Sprite* get_sprite();
};