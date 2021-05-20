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
    sf::Vector2i score;
    std::pair<sf::Text, sf::Text> numbers;
    float factorX;
    float factorY;

    public:
    Scoreboard() = default;
    Scoreboard(std::string imagepath, sf::Vector2f& windowsize, const std::string);
    void update(sf::Vector2i score_given);
    void draw(sf::RenderWindow& window);
    sf::Vector2u getSize();
};