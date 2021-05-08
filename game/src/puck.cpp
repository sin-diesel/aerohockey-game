#include "../include/puck.h"

sf::Vector2f Puck::update(sf::Vector2f pos_striker1, sf::Vector2f pos_striker2)
{
    sf::Vector2f pos = position += speed;
    sf::Vector2f diff1 = pos - pos_striker1;
    sf::Vector2f diff2 = pos - pos_striker2;
    /*if (abs(diff1.x)*abs(diff1.x)+abs(diff1.y)*abs(diff1.y) < RADIUS*RADIUS) {
        // speed changes
    }
    if (abs(diff2.x)*abs(diff2.x)+abs(diff2.y)*abs(diff2.y) < RADIUS*RADIUS) {
        // speed changes
    }*/
    if (pos.x == MAX_POS_X || pos.x == MIN_POS_X) {
        speed.x = speed.x * -1;
    }
    if (pos.y == MAX_POS_Y || pos.y == MIN_POS_Y) {
        speed.y = speed.y * -1;
    }
    return pos;


sf::Vector2f Puck::get_coord()
{
    return position;
}
        
void Striker::calculate_speed(sf::Vector2f pos) 
{
    speed = pos - position;
}

sf::Sprite* Puck::get_sprite()
{
    return sprite;
}