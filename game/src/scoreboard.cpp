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

void Scoreboard::draw(sf::RenderWindow& window)
{
    //window.draw(sprite);
}
