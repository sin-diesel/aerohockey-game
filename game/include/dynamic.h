#pragma once
#include "library.h"
#define MAX_POS_X 1817
#define MAX_POS_Y 795
#define MIN_POS_X 103
#define MIN_POS_Y 94
#define DEFAULT_MASS 10
#define DEFAULT_RADIUS 50
#define PUCK_RADIUS 15
#define STRIKER_RADIUS 30
#define PUCK_MASS 10
#define STRIKER_MASS 100
#define GATE_POS_X_LEFT 90
#define GATE_POS_X_RIGHT 1765
#define GATE_POS_Y_UPPER 690
#define GATE_POS_Y_DOWNER 420
#define CENTER_X 960
#define CENTER_Y 468
#define CYCLE_SPEED 15
#define SPEED_LIMIT 15
#define EPSILON 0.0001

const float MAX_SPEED = 300;

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
    ClientDynamicObject(std::string imagepath, sf::Vector2f pos, sf::Vector2f windowsize);
    void draw(sf::RenderWindow& window);
};

class ServerDynamicObject : public DynamicObject {
    private:
    sf::Vector2f speed;
    const int number;
    const float radius;
    const float mass;
    std::pair<bool, bool> collision = {false, false};
    public:
    ServerDynamicObject() = default;
    ServerDynamicObject(float mass, float radius, float pos1, float pos2, int num);
    float get_mass();
    float get_radius();
    sf::Vector2f get_speed();
    void set_speed(sf::Vector2f speed_given);
    void keyboard_change_speed(std::vector<int>& key);
    void keyboard_update_speed();
    int check_score();
    sf::Vector2f update(ServerDynamicObject&, ServerDynamicObject&);
    sf::Vector2f calculate_speed(sf::Vector2f);
};