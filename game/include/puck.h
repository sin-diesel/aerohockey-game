#pragma once
#include "game.h"

class Puck {
    private:
    sf::Vector2f position;
    sf::Vector2f speed;
    public:
    sf::Vector2f update();
    void change_speed(sf::Vector2f pos);
};