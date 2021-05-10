#include "../include/dynamic.h"

DynamicObject::DynamicObject(std::string imagepath)
{
    this->imagepath = imagepath;
    image.loadFromFile(imagepath);
    image.createMaskFromColor(sf::Color::White);
    texture.loadFromImage(image);
    sprite.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
}

void DynamicObject::draw(sf::RenderWindow& window)
{
    sprite.setTexture(texture);
    sprite.setPosition(position);
    window.draw(sprite);
}

void DynamicObject::set_coord(sf::Vector2f new_pos)
{
    position = new_pos;
}  

sf::Vector2f DynamicObject::update(sf::Vector2f pos_striker1, sf::Vector2f pos_striker2)
{
    sf::Vector2f pos = position += speed;
    sf::Vector2f diff1 = pos - pos_striker1;
    sf::Vector2f diff2 = pos - pos_striker2;
    /*if (abs(diff1.x)*abs(diff1.x)+abs(diff1.y)*abs(diff1.y) < RADIUS*RADIUS) {
        // speed changes
    }
    if (abs(diff2.x)*abs(diff2.x)+abs(diff2.y)*abs(diff2.y) < RADIUS*RADIUS) {
        // speed changes
    }*/
    if (pos.x == MAX_POS_X || pos.x == MIN_POS_X) {
        speed.x = speed.x * -1;
    }
    if (pos.y == MAX_POS_Y || pos.y == MIN_POS_Y) {
        speed.y = speed.y * -1;
    }
    return pos;
}

sf::Vector2f DynamicObject::get_coord()
{
    return position;
}
        
void DynamicObject::calculate_speed(sf::Vector2f pos) 
{
    speed = pos - position;
}



