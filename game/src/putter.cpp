#include "../include/putter.h"

void Putter::update(float posx, float posy)
{
    position.x = posx;
    position.y = posy;
}

void Putter::change_speed(float speedx, float speedy)
{
    this->speed.x = speedx;
    this->speed.y = speedy;
}