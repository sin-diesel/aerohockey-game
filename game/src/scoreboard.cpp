#include "../include/scoreboard.h"

Scoreboard::Scoreboard(std::string imagepath, sf::Vector2f position)
{
    this->imagepath = imagepath;
    image.loadFromFile(imagepath);
    sprite.setOrigin(image.getSize().x / 2, 0);
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
    sprite.setTexture(image);
    window.draw(sprite);
}
