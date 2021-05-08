#pragma once
#include "game.h"

class Putter {
    private:
    sf::Vector2f position;
    sf::Vector2f speed;
    sf::Sprite sprite;

    public:
    Putter();
    void update(float posx, float posy);
    void change_speed(float speedx, float speedy);
    sf::Sprite* get_sprite();
};