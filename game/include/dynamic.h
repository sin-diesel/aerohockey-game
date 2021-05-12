#pragma once
#include "library.h"
#define MAX_POS_X 1750
#define MAX_POS_Y 965
#define MIN_POS_X 115
#define MIN_POS_Y 175
#define RADIUS 50
#define DEFAULT_MASS 10

class DynamicObject {
    protected:
    //POSITION
    public:
    sf::Vector2f position;
    void set_coord(sf::Vector2f new_pos);
    sf::Vector2f get_coord();

};

class ClientDynamicObject : public DynamicObject {
    private:
    sf::Image image;
    sf::Texture texture;
    sf::Sprite sprite;
    std::string imagepath;

    public:
    ClientDynamicObject() = default;
    ClientDynamicObject(std::string imagepath, sf::Vector2f);
    void draw(sf::RenderWindow& window);
};

class ServerDynamicObject : public DynamicObject {
    private:
    sf::Vector2f speed;

    public:
    const float mass;
    ServerDynamicObject();
    ServerDynamicObject(float);
    sf::Vector2f update(ServerDynamicObject&, ServerDynamicObject&);
    sf::Vector2f calculate_speed(sf::Vector2f);
    sf::Vector2f calculate_speed();
};