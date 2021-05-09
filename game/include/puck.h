#pragma once
#include "library.h"

#define MAX_POS_X 200
#define MAX_POS_Y 200
#define MIN_POS_X 0
#define MIN_POS_Y 0
#define RADIUS 10
class Puck {
    protected:
    sf::Vector2f position;
    sf::Vector2f speed;
    sf::Sprite sprite;

    public:
    Puck() = default;
    Puck(std::string imagepath);
    sf::Vector2f update(sf::Vector2f, sf::Vector2f);
    sf::Vector2f get_coord();
    void draw(sf::RenderWindow& window);
};

class Striker : public Puck {
    public:
    Striker();
    void calculate_speed(sf::Vector2f);
};