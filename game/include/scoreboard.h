#pragma once
#include "library.h"

class Scoreboard {
    private:

    sf::Sprite sprite;
    bool scored;

    public:
    Scoreboard();
    void update();
    bool goalscored();
    void unscored();
    void draw(sf::RenderWindow& window);
};