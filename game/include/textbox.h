#pragma once
#include "library.h"
#define BACKSPACE 0x8

class TextBox{

    private:

    const sf::Font* font;
    sf::RectangleShape box ;
    sf::Text text ;
    sf::String text_s ;
    bool textChanged ;

    public:

    TextBox() = default;
    TextBox(sf::Text& suggestion);

    void draw(sf::RenderWindow& window);
    std::string get_text();
    void update(sf::Event& event);
};