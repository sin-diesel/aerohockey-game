#include "scoreboard.h"

Scoreboard::Scoreboard(std::string imagepath, sf::Vector2f& windowsize, const std::string path)
{
    this->imagepath = imagepath;
    position = sf::Vector2f(windowsize.x / 2, 0);
    image.loadFromFile(imagepath);
    image.createMaskFromColor(sf::Color::White);
    texture.loadFromImage(image);
    sprite.setOrigin(texture.getSize().x / 2, 0);
    sprite.setPosition(position.x, position.y);
    factorX = windowsize.x / DEFAULT_WIDTH;
    factorY = windowsize.y / DEFAULT_HEIGHT;
    sprite.setScale(factorX, factorY);

    score.x = 0;
    score.y = 0;
    fontpath = path + "/game/images/arial.ttf";
    font.loadFromFile(fontpath);
    numbers.first.setFillColor(sf::Color::Black);
    numbers.second.setFillColor(sf::Color::Black);
    numbers.first.setStyle(sf::Text::Bold);
    numbers.second.setStyle(sf::Text::Bold);

    unsigned int charsize = static_cast<unsigned int>(60 * std::min(factorX, factorY));
    numbers.first.setCharacterSize(charsize);
    numbers.second.setCharacterSize(charsize);
}

void Scoreboard::update(sf::Vector2i score_given)
{
    score = score_given;
}

void Scoreboard::draw(sf::RenderWindow& window)
{
    sprite.setTexture(texture);
    numbers.first.setFont(font);
    numbers.second.setFont(font);

    numbers.first.setString(std::to_string(score.x));
    numbers.second.setString(std::to_string(score.y));
    numbers.first.setOrigin(numbers.first.getLocalBounds().width / 2, numbers.first.getLocalBounds().height);
    numbers.second.setOrigin(numbers.second.getLocalBounds().width / 2, numbers.second.getLocalBounds().height);
    float v_padding  = factorY * static_cast<float>(texture.getSize().y) / 2;
    float h_padding = factorX * static_cast<float>(texture.getSize().x) / 4; 
    numbers.first.setPosition(position.x - h_padding, position.y + v_padding);
    numbers.second.setPosition(position.x + h_padding, position.y + v_padding);

    window.draw(sprite);
    window.draw(numbers.first);
    window.draw(numbers.second);
}

sf::Vector2u Scoreboard::getSize()
{
    return texture.getSize();
}
