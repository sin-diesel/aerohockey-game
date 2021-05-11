#pragma once
#include "library.h"

class Scoreboard {
    private:

    std::string imagepath;
    std::string fontpath;
    sf::Vector2f position;
    sf::Image image;
    sf::Texture texture;
    sf::Sprite sprite;
    sf::Font font;
    std::pair<int, int> score;
    std::pair<sf::Text, sf::Text> numbers;

    public:
    Scoreboard() = default;
    Scoreboard(std::string imagepath, sf::Vector2f position_, const std::string);
    void update();
    void draw(sf::RenderWindow& window);
    sf::Vector2u getSize();
};