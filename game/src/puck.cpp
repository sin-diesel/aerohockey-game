#include "../include/puck.h"


Puck::Puck()
{
    
}

void Puck::update(float posx, float posy)
{
    position.x = posx;
    position.y = posy;
}

void Puck::change_speed(float speedx, float speedy)
{
    this->speed.x = speedx;
    this->speed.y = speedy;
}

sf::Sprite* Puck::get_sprite()
{
    return sprite;
}