#pragma once
#include "library.h"

#define MAX_POS_X 200
#define MAX_POS_Y 200
#define MIN_POS_X 0
#define MIN_POS_Y 0
#define RADIUS 10
class DynamicObject {
    protected:
    std::string imagepath;
    sf::Vector2f position;
    sf::Vector2f speed;
    sf::Image image;
    sf::Texture texture;
    sf::Sprite sprite;

    public:
    DynamicObject() = default;
    DynamicObject(std::string imagepath);
    sf::Vector2f update(sf::Vector2f, sf::Vector2f);
    sf::Vector2f get_coord();
    void set_coord(sf::Vector2f new_pos);
    void draw(sf::RenderWindow& window);
    void calculate_speed(sf::Vector2f);
};