#include "../include/dynamic.h"
#include "../include/library.h"
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
    float dist1 = sqrt((diff1.x)*(diff1.x)+(diff1.y)*(diff1.y));
    sf::Vector2f diff2 = position - striker2.position;
    float dist2 = sqrt((diff2.x)*(diff2.x)+(diff2.y)*(diff2.y));
    float radius_sum = PUCK_RADIUS + STRIKER_RADIUS;

    if (dist1 < radius_sum * 0.96) {
        std::cout << "Collision" << std::endl;
        std::cout << "BSPEED1 " << speed.x << " " << speed.y << std::endl;
        float mult1 = (striker1.get_speed().x - speed.x) * diff1.x + (striker1.get_speed().y - speed.y) * diff1.y;
        if (dist1 > EPSILON) {
                speed += static_cast<float> (2) * diff1  * striker1.get_mass() * mult1 / (striker1.get_mass() + mass) / dist1 / dist1;
                position = striker1.position + (position - striker1.position) * (radius_sum / dist1); 
        }
        std::cout << "ASPEED1 " << speed.x << " " << speed.y << std::endl;
    }
    if (dist2 <radius_sum) {
        if (!collision.second) {
            collision.second = true;
            std::cout << "BSPEED2 " << speed.x << " " << speed.y << std::endl;
            float mult2 = (striker2.get_speed().x - speed.x) * diff2.x + (striker2.get_speed().y - speed.y) * diff2.y;
            if (dist2 > EPSILON)
                speed += static_cast<float> (2) * diff2  * striker2.get_mass() * mult2 / (striker2.get_mass() + mass) / dist2 / dist2;
            std::cout << "ASPEED2 " << speed.x << " " << speed.y << std::endl;
        }

        if (dist2 >= EPSILON) 
            position = striker2.position + (position - striker2.position) * (radius_sum / dist2); 
    }
    else {
        collision.second = false;
    }
    if (position.x >= MAX_POS_X - PUCK_RADIUS || position.x <= MIN_POS_X + PUCK_RADIUS) {
        speed.x = speed.x * -1;
    }
    if (position.y >= MAX_POS_Y - PUCK_RADIUS || position.y <= MIN_POS_Y + PUCK_RADIUS) {
        speed.y = speed.y * -1;
    }
    
    speed *= static_cast<float>(0.997);
    float speed_val = sqrt(speed.x*speed.x + speed.y*speed.y);
    if (speed_val > MAX_SPEED)
        speed *= (MAX_SPEED / speed_val);
    position += (speed / static_cast<float> (CYCLE_SPEED));
    position.x = (position.x < MIN_POS_X + PUCK_RADIUS) ? MIN_POS_X + PUCK_RADIUS : position.x;
    position.y = (position.y < MIN_POS_Y + PUCK_RADIUS) ? MIN_POS_Y + PUCK_RADIUS : position.y;
    position.x = (position.x > MAX_POS_X - PUCK_RADIUS) ? MAX_POS_X - PUCK_RADIUS : position.x;
    position.y = (position.y > MAX_POS_Y - PUCK_RADIUS) ? MAX_POS_Y - PUCK_RADIUS : position.y;
    std::cout << "Puck speed: " << speed.x << " " << speed.y << std::endl;
    return position;
}

int ServerDynamicObject::check_score()
{
    //std::cout << "CHECK SCORE" << std::endl;
    if (position.x < GATE_POS_X_LEFT && position.y < GATE_POS_Y_UPPER && position.y > GATE_POS_Y_DOWNER) {
        position.x = CENTER_X, position.y = CENTER_Y, speed.x = 0, speed.y = 0;
        return 1;
    }
    if (position.x > GATE_POS_X_RIGHT && position.y < GATE_POS_Y_UPPER && position.y > GATE_POS_Y_DOWNER) {
        position.x = CENTER_X, position.y = CENTER_Y, speed.x = 0, speed.y = 0;
        return 2;
    }
    return 0;
}

sf::Vector2f DynamicObject::get_coord()
{
    return position;
}

sf::Vector2f ServerDynamicObject::calculate_speed(sf::Vector2f pos) 
{
    speed = pos - position;
    //std::cout << "SPED1 " << speed.x << " " << speed.y << std::endl;
    if (position.x >= MAX_POS_X - STRIKER_RADIUS && speed.x > 0)
        speed.x = 0;
    if (position.y >= MAX_POS_Y - STRIKER_RADIUS && speed.y > 0)
        speed.y = 0;
    if (position.x <= MIN_POS_X + STRIKER_RADIUS && speed.x < 0)
        speed.x = 0;
    if (position.y <= MIN_POS_Y + STRIKER_RADIUS && speed.y < 0)
        speed.y = 0;
    pos.x = (speed.x == 0) ? 0 : pos.x, pos.y = (speed.y == 0) ? 0 : pos.y;
    set_coord(pos);
    //std::cout << "SPED2 " << speed.x << " " << speed.y << std::endl;
    return speed;
}

sf::Vector2f ServerDynamicObject::get_speed() 
{
    return speed;
}

void ServerDynamicObject::keyboard_change_speed(int key)
{
    if (key == sf::Keyboard::W && (position.y - STRIKER_RADIUS > MIN_POS_Y))
        speed.y += -1;
    else if (key == sf::Keyboard::S && (position.y + STRIKER_RADIUS < MAX_POS_Y))
        speed.y += 1;
    else if (key == sf::Keyboard::D && (position.x + STRIKER_RADIUS < MAX_POS_X))
        speed.x += 1;
    else if (key == sf::Keyboard::A && (position.x - STRIKER_RADIUS > MIN_POS_X))
        speed.x += -1;
}

void ServerDynamicObject::keyboard_update_speed()
{
    if (position.y - STRIKER_RADIUS < MIN_POS_Y && speed.y < 0) {
        speed.y = 0;
    }
    if (position.y + STRIKER_RADIUS > MAX_POS_Y && speed.y > 0) {
        speed.y = 0;
    }
    if (position.x + STRIKER_RADIUS > MAX_POS_X && speed.x > 0) {
        speed.x = 0;
    }
    if (position.x - STRIKER_RADIUS < MIN_POS_X && speed.x < 0) {
        speed.x = 0;
    }
    position += speed / static_cast<float> (5);
}

void ServerDynamicObject::set_speed(sf::Vector2f speed_given)
{
    speed += speed_given;
}

float ServerDynamicObject::get_radius()
{
    return radius;
}

float ServerDynamicObject::get_mass()
{
    return mass;
}
ServerDynamicObject::ServerDynamicObject(float mass, float radius, float pos1, float pos2): mass(mass), radius(radius) {position.x = pos1, position.y = pos2;}