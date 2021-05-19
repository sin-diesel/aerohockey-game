#pragma once
#include "library.h"
#define MAX_POS_X 1785
#define MAX_POS_Y 1000
#define MIN_POS_X 70
#define MIN_POS_Y 145
#define DEFAULT_MASS 10
#define DEFAULT_RADIUS 50
#define PUCK_RADIUS 15
#define STRIKER_RADIUS 30
#define PUCK_MASS 10
#define STRIKER_MASS 100
#define GATE_POS_X_LEFT 140
#define GATE_POS_X_RIGHT 1715
#define GATE_POS_Y_UPPER 800
#define GATE_POS_Y_DOWNER 200
#define CYCLE_SPEED 15
const float MAX_SPEED=30;

class DynamicObject {
    protected:
    sf::Vector2f position;
    public:
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
    int collision1, collision2;
    const float radius;
    const float mass;

    public:
    ServerDynamicObject();
    ServerDynamicObject(float rad);
    ServerDynamicObject(float mass, float radius);
    float get_mass();
    float get_radius();
    int check_score();
    sf::Vector2f update(ServerDynamicObject&, ServerDynamicObject&);
    sf::Vector2f calculate_speed(sf::Vector2f);
    sf::Vector2f calculate_speed();
};