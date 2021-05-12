#include "../include/dynamic.h"

ClientDynamicObject::ClientDynamicObject(std::string imagepath)
{
    this->imagepath = imagepath;
    image.loadFromFile(imagepath);
    image.createMaskFromColor(sf::Color::White);
    texture.loadFromImage(image);
    sprite.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
}

void ClientDynamicObject::draw(sf::RenderWindow& window)
{
    sprite.setTexture(texture);
    sprite.setPosition(position);
    window.draw(sprite);
}

void DynamicObject::set_coord(sf::Vector2f new_pos)
{
    position = new_pos;
}

sf::Vector2f ServerDynamicObject::update(ServerDynamicObject& striker1, ServerDynamicObject& striker2)
{
    sf::Vector2f diff1 = position - striker1.position;
    sf::Vector2f diff2 = position - striker2.position;
    if ((diff1.x)*(diff1.x)+(diff1.y)*(diff1.y) <= RADIUS*RADIUS) {
        speed = ((mass-striker1.mass)*speed+2*striker1.mass*striker1.calculate_speed())/(mass+striker1.mass);
    }
    if ((diff2.x)*(diff2.x)+(diff2.y)*(diff2.y) <= RADIUS*RADIUS) {
        speed = ((mass-striker2.mass)*speed+2*striker2.mass*striker2.calculate_speed())/(mass+striker2.mass);
    }
    if (position.x == MAX_POS_X || position.x == MIN_POS_X) {
        speed.x = speed.x * -1;
    }
    if (position.y == MAX_POS_Y || position.y == MIN_POS_Y) {
        speed.y = speed.y * -1;
    }
    return position += speed;
}

sf::Vector2f DynamicObject::get_coord()
{
    return position;
}
        
sf::Vector2f ServerDynamicObject::calculate_speed(sf::Vector2f pos) 
{
    speed = pos - position;
    if (position.x <= MAX_POS_X - RADIUS && speed.x > 0)
        speed.x = 0;
    if (position.y <= MAX_POS_Y - RADIUS && speed.y > 0)
        speed.y = 0;
    if (position.x >= MIN_POS_X + RADIUS && speed.x < 0)
        speed.x = 0;
    if (position.y >= MIN_POS_Y + RADIUS && speed.y < 0)
        speed.y = 0;
    pos.x = (speed.x == 0) ? 0 : pos.x, pos.y = (speed.y == 0) ? 0 : pos.y;
    set_coord(pos);
    return speed;
}

sf::Vector2f ServerDynamicObject::calculate_speed() 
{
    return speed;
}

ServerDynamicObject::ServerDynamicObject(): mass(DEFAULT_MASS) {}
ServerDynamicObject::ServerDynamicObject(float mass): mass(mass) {}

