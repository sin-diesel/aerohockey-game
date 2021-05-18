#include "../include/dynamic.h"
#include "library.h"
ClientDynamicObject::ClientDynamicObject(std::string imagepath, sf::Vector2f pos)
{
    this->imagepath = imagepath;
    position = pos;
    image.loadFromFile(imagepath);
    image.createMaskFromColor(sf::Color::White);
    texture.loadFromImage(image);
    sprite.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
}

void ClientDynamicObject::draw(sf::RenderWindow& window)
{
    sprite.setTexture(texture);
    sprite.setPosition(position);
    window.draw(sprite);
}

void DynamicObject::set_coord(sf::Vector2f new_pos)
{
    position = new_pos;
}

sf::Vector2f ServerDynamicObject::update(ServerDynamicObject& striker1, ServerDynamicObject& striker2)
{
    sf::Vector2f diff1 = position - striker1.position;
    sf::Vector2f diff2 = position - striker2.position;
    float radius_sum = PUCK_RADIUS + STRIKER_RADIUS;
    //std::cout << "DIFF " << diff1.x << " " << diff1.y << " " << diff2.x << " " <<  diff2.y << std::endl;
    //std::cout << "striker position " << striker1.position.x << " " << striker1.position.y << " " << striker2.position.x << " " <<  striker2.position.y << std::endl;
    
    if ((diff1.x)*(diff1.x)+(diff1.y)*(diff1.y) <= radius_sum*radius_sum) {
        if (!collision1) {
            collision1 = 1;
            std::cout << "BSPEED1 " << speed.x << " " << speed.y << " " << striker1.calculate_speed().x << " " << striker1.calculate_speed().y << std::endl;
            speed = (((mass-striker1.get_mass())*speed+striker1.calculate_speed()*static_cast<float> (2*striker1.get_mass()))/(mass+striker1.get_mass()));
            striker1.speed = ((striker1.calculate_speed()*(striker1.get_mass()-mass)+speed*static_cast<float> (2*mass))/(mass+striker1.get_mass()));
            std::cout << "ASPEED1 " << speed.x << " " << speed.y << " " << striker1.calculate_speed().x << " " << striker1.calculate_speed().y << std::endl;
        }
    }
    else {
        collision1 = 0;
    }
    if ((diff2.x)*(diff2.x)+(diff2.y)*(diff2.y) <= radius_sum*radius_sum) {
        if (!collision2) {
            collision2 = 1;
            std::cout << "BSPEED2 " << speed.x << " " << speed.y << " " << striker2.calculate_speed().x << " " << striker2.calculate_speed().y << std::endl;
            speed = (((mass-striker2.get_mass())*speed+striker2.calculate_speed()*static_cast<float> (2*striker2.get_mass()))/(mass+striker2.get_mass()));
            striker2.speed = ((striker2.calculate_speed()*(striker2.get_mass()-mass)+speed*static_cast<float> (2*mass))/(mass+striker2.get_mass()));
            std::cout << "ASPEED2 " << speed.x << " " << speed.y << " " << striker2.calculate_speed().x << " " << striker2.calculate_speed().y << std::endl;
        }
    }
    else {
        collision2 = 0;
    }
    if (position.x >= MAX_POS_X - PUCK_RADIUS || position.x <= MIN_POS_X + PUCK_RADIUS) {
        speed.x = speed.x * -1;
    }
    if (position.y >= MAX_POS_Y - PUCK_RADIUS || position.y <= MIN_POS_Y + PUCK_RADIUS) {
        speed.y = speed.y * -1;
    }
    if (position.x < MIN_POS_X || position.x > MAX_POS_X || position.y > MAX_POS_X || position.y < MIN_POS_Y)
        position.x = 925, position.y = 570;
    sf::Vector2f sp1 = striker1.calculate_speed(), sp2 = striker2.calculate_speed();
    //std::cout << "SPEED_STRIKERS " << sp1.x << " " << sp1.x << " " << sp2.x << " " << sp2.y << std::endl;
    //std::cout << "SPEED " << speed.x << " " << speed.y << std::endl;
    return position += (speed / static_cast<float> (CYCLE_SPEED));
}

int ServerDynamicObject::check_score()
{
    //std::cout << "CHECK SCORE" << std::endl;
    if (position.x < GATE_POS_X_LEFT && position.y < GATE_POS_Y_UPPER && position.y > GATE_POS_Y_DOWNER) {
        position.x = 925, position.y = 570, speed.x = 0, speed.y = 0;
        return 1;
    }
    if (position.x > GATE_POS_X_RIGHT && position.y < GATE_POS_Y_UPPER && position.y > GATE_POS_Y_DOWNER) {
        position.x = 925, position.y = 570, speed.x = 0, speed.y = 0;
        return 2;
    }
    return 0;
}

sf::Vector2f DynamicObject::get_coord()
{
    return position;
}

sf::Vector2f ServerDynamicObject::calculate_speed(sf::Vector2f pos) 
{
    speed = pos - position;
    //std::cout << "SPED1 " << speed.x << " " << speed.y << std::endl;
    if (position.x >= MAX_POS_X - STRIKER_RADIUS && speed.x > 0)
        speed.x = 0;
    if (position.y >= MAX_POS_Y - STRIKER_RADIUS && speed.y > 0)
        speed.y = 0;
    if (position.x <= MIN_POS_X + STRIKER_RADIUS && speed.x < 0)
        speed.x = 0;
    if (position.y <= MIN_POS_Y + STRIKER_RADIUS && speed.y < 0)
        speed.y = 0;
    pos.x = (speed.x == 0) ? 0 : pos.x, pos.y = (speed.y == 0) ? 0 : pos.y;
    set_coord(pos);
    //std::cout << "SPED2 " << speed.x << " " << speed.y << std::endl;
    return speed;
}

sf::Vector2f ServerDynamicObject::calculate_speed() 
{
    return speed;
}

float ServerDynamicObject::get_radius()
{
    return radius;
}

float ServerDynamicObject::get_mass()
{
    return mass;
}

ServerDynamicObject::ServerDynamicObject(): mass(DEFAULT_MASS), radius(DEFAULT_RADIUS) {}
ServerDynamicObject::ServerDynamicObject(float rad): mass(DEFAULT_MASS), radius(rad) {}
ServerDynamicObject::ServerDynamicObject(float mass, float radius): mass(mass), radius(radius) {}