#pragma once
#include "library.h"

class Scoreboard {
    private:

    std::string imagepath;
    sf::Texture image;
    sf::Sprite sprite;
    bool scored;

    public:
    Scoreboard() = default;
    Scoreboard(std::string imagepath, sf::Vector2f position);
    void update();
    bool goalscored();
    void unscored();
    void draw(sf::RenderWindow& window);
};