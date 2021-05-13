#include "../include/dynamic.h"

ClientDynamicObject::ClientDynamicObject(std::string imagepath, sf::Vector2f pos)
{
    this->imagepath = imagepath;
    position = pos;
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
    //std::cout << "DIFF " << diff1.x << " " << diff1.y << " " << diff2.x << " " <<  diff2.y << std::endl;
    //std::cout << "striker position " << striker1.position.x << " " << striker1.position.y << " " << striker2.position.x << " " <<  striker2.position.y << std::endl;
    if ((diff1.x)*(diff1.x)+(diff1.y)*(diff1.y) <= RADIUS*RADIUS && !collision1) {
        collision1 = 1;
        std::cout << "COLLISION " << collision1 << std::endl;
        std::cout << "BSPEED1 " << speed.x << " " << speed.y << " " << striker1.calculate_speed().x << " " << striker1.calculate_speed().y << std::endl;
        speed = (((mass-100)*speed+striker1.calculate_speed()*static_cast<float> (2*100))/(mass+100));
        striker1.speed = ((striker1.calculate_speed()*(100-mass)+speed*static_cast<float> (2*mass))/(mass+100));
        std::cout << "ASPEED1 " << speed.x << " " << speed.y << " " << striker1.calculate_speed().x << " " << striker1.calculate_speed().y << std::endl;
    }
    collision1 = 0;
    if ((diff2.x)*(diff2.x)+(diff2.y)*(diff2.y) <= RADIUS*RADIUS && !collision2) {
        collision2 = 1;
        std::cout << "COLLISION " << collision1 << std::endl;
        std::cout << "BSPEED2 " << speed.x << " " << speed.y << " " << striker2.calculate_speed().x << " " << striker2.calculate_speed().y << std::endl;
        speed = (((mass-100)*speed+striker2.calculate_speed()*static_cast<float> (2*100))/(mass+100));
        striker2.speed = ((striker2.calculate_speed()*(100-mass)+speed*static_cast<float> (2*mass))/(mass+100));
        std::cout << "ASPEED2 " << speed.x << " " << speed.y << " " << striker2.calculate_speed().x << " " << striker2.calculate_speed().y << std::endl;
    }
    collision2 = 0;
    if (position.x >= MAX_POS_X - RADIUS/2 || position.x <= MIN_POS_X + RADIUS/2) {
        speed.x = speed.x * -1;
    }
    if (position.y >= MAX_POS_Y - RADIUS/2 || position.y <= MIN_POS_Y + RADIUS/2) {
        speed.y = speed.y * -1;
    }
    if (position.x < MIN_POS_X || position.x > MAX_POS_X || position.y > MAX_POS_X || position.y < MIN_POS_Y)
        position.x = 600, position.y = 600;
    sf::Vector2f sp1 = striker1.calculate_speed(), sp2 = striker2.calculate_speed();
    //std::cout << "SPEED_STRIKERS " << sp1.x << " " << sp1.x << " " << sp2.x << " " << sp2.y << std::endl;
    //std::cout << "SPEED " << speed.x << " " << speed.y << std::endl;
    return position += (speed / static_cast<float> (50));
}



sf::Vector2f DynamicObject::get_coord()
{
    return position;
}

sf::Vector2f ServerDynamicObject::calculate_speed(sf::Vector2f pos) 
{
    speed = pos - position;
    //std::cout << "SPED1 " << speed.x << " " << speed.y << std::endl;
    if (position.x >= MAX_POS_X - RADIUS && speed.x > 0)
        speed.x = 0;
    if (position.y >= MAX_POS_Y - RADIUS && speed.y > 0)
        speed.y = 0;
    if (position.x <= MIN_POS_X + RADIUS && speed.x < 0)
        speed.x = 0;
    if (position.y <= MIN_POS_Y + RADIUS && speed.y < 0)
        speed.y = 0;
    pos.x = (speed.x == 0) ? 0 : pos.x, pos.y = (speed.y == 0) ? 0 : pos.y;
    set_coord(pos);
    //std::cout << "SPED2 " << speed.x << " " << speed.y << std::endl;
    return speed;
}

sf::Vector2f ServerDynamicObject::calculate_speed() 
{
    return speed;
}

ServerDynamicObject::ServerDynamicObject(): mass(DEFAULT_MASS), collision1(0), collision2(0) {}
ServerDynamicObject::ServerDynamicObject(float mass): mass(mass) {}