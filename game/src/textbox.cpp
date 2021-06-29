#include "textbox.h"

TextBox::TextBox(sf::Text& suggestion)
{
    sf::FloatRect bounds(suggestion.getGlobalBounds());
    box.setSize({bounds.width, bounds.height});
    box.setFillColor(sf::Color::White);
    sf::Vector2f origin(box.getSize().x / 2, box.getSize().y / 2);
    box.setOrigin(origin);
    sf::Vector2f position(suggestion.getPosition().x, suggestion.getPosition().y + 2 * origin.y);
    box.setPosition(position);

    font = suggestion.getFont();
    text.setFillColor(sf::Color::Black);
    unsigned int default_char_size = static_cast<unsigned int>(suggestion.getCharacterSize() * 0.7);
    text.setCharacterSize(default_char_size);
    text.setOrigin({0, origin.y});
    text.setPosition({bounds.left, position.y});
   
}

void TextBox::draw(sf::RenderWindow& window)
{
    text.setFont(*font);
    text.setString(text_s);

    float text_width = text.getLocalBounds().width;
    float box_width = box.getLocalBounds().width;
    float factor = (text_width >= box_width) ? (0.94 * box_width / text_width) : 1;
    text.setScale(factor, factor);
    window.draw(box);
    window.draw(text);
}

std::string TextBox::get_text()
{
    return text.getString().toAnsiString();
}

void TextBox::update(sf::Event& event)
{
    switch ( event.text.unicode ) {
        case BACKSPACE:
        if ( !text_s.isEmpty() )
            text_s.erase(text_s.getSize()-1) ;
        break ;
        default :
             text_s += static_cast<wchar_t>(event.text.unicode) ;
             //std::cout << "new: " << text_s.toAnsiString() << std::endl;
        }
}
