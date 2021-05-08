#include "puck.h"

void Puck::update(float* posx, float* posy)
{
    *posx = this->position.x += this->speed.x;
    *posy = this->position.y += this->speed.y;
}

void Puck::change_speed(float speedx, float speedy)
{
    this->speed.x = speedx;
    this->speed.y = speedy;
}