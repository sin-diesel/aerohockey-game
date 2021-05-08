#include "../include/scoreboard.h"

Scoreboard::Scoreboard()
{
    
}

void Scoreboard::update()
{
    
}

bool Scoreboard::goalscored()
{
    return scored;
}

void Scoreboard::unscored()
{
    scored = false;
}

sf::Sprite* Puck::get_sprite()
{
    return sprite;
}

