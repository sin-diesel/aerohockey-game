#include "../include/scoreboard.h"

Scoreboard::Scoreboard(std::string imagepath)
{
    this->imagepath = imagepath;
    image.loadFromFile(imagepath);
    sprite.setTexture(image);
    sprite.setPosition(50, 50);
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
