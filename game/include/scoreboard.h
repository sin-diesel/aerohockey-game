#pragma once
#include "library.h"

class Scoreboard {
    private:

    std::string imagepath;
    std::string fontpath;
    sf::Vector2f position;
    sf::Texture image;
    sf::Sprite sprite;
    sf::Font font;
    std::pair<int, int> score;
    std::pair<sf::Text, sf::Text> numbers;

    public:
    Scoreboard() = default;
    Scoreboard(std::string imagepath, sf::Vector2f position_);
    void update();
    void draw(sf::RenderWindow& window);
};