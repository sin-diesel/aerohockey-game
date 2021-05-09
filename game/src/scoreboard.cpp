#include "../include/scoreboard.h"

Scoreboard::Scoreboard(std::string imagepath, sf::Vector2f position)
{
    this->imagepath = imagepath;
    image.loadFromFile(imagepath);
    sprite.setTexture(image);
    sprite.setPosition(position.x, position.y);
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
    window.draw(sprite);
}
