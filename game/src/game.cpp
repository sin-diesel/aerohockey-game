#include "../include/game.h"
#include <stdio.h>
#include <sys/utsname.h>

//const char path[] = "/Users/stassidelnikov/aerohockey-game";

Game::Game(sf::Vector2u windowsize_, int number_) {

    struct utsname details;
    int ret = uname(&details);

    if (ret == 0)
    {
        printf("Sysname: %s\n", details.sysname);
    }

    #ifdef __MACH__
        path = std::string("/Users/stassidelnikov/aerohockey-game");
    #else
        path = std::experimental::filesystem::current_path().string();
    #endif
    this->number = number;
    sf::Vector2f windowsize = sf::Vector2f(windowsize_);
    scoreboard = Scoreboard(path + "/game/images/scoreboard.png", {windowsize.x/2, 0}, path);  
    striker1 = ClientDynamicObject(path + "/game/images/striker.png");
    striker2 = ClientDynamicObject(path + "/game/images/striker.png");
    puck = ClientDynamicObject(path + "/game/images/puck.png");
   
    puck.set_coord({windowsize.x / 2, windowsize.y / 2});  //temporary, just to look vizualization
    striker2.set_coord({windowsize.x * 3 / 4, windowsize.y / 2});  //temporary, just to look vizualization
}

void Game::play(sf::RenderWindow& window) {

    //get structure of coordinates and score from socket

    //striker1.update({50, 50}, {0, 0});
    //striker2.update({100, 50}, {0, 0});
    //puck.update({150, 50}, {0, 0});
    //scoreboard.update();
    sf::Vector2f mouse_pos = sf::Vector2f(sf::Mouse::getPosition(window));
    if (number == 1)
        striker1.set_coord(mouse_pos); //temporary, just to look vizualization
    else
        striker2.set_coord(mouse_pos);
}

void Game::draw_objects(sf::RenderWindow& window) {
    striker1.draw(window);
    striker2.draw(window);
    puck.draw(window);
    scoreboard.draw(window);
}

Game::~Game() {
    
}

void Game::render() {

}

void Game::update() {

}

sf::Packet& operator <<(sf::Packet& packet, const sf::Vector2f& pos)
{
    return packet << pos.x << pos.y;
}

sf::Packet& operator >>(sf::Packet& packet, sf::Vector2f& pos)
{
    return packet >> pos.x >> pos.y;
}

sf::Packet& operator <<(sf::Packet& packet, const sf::Vector2i& pos)
{
    return packet << pos.x << pos.y;
}

sf::Packet& operator >>(sf::Packet& packet, sf::Vector2i& pos)
{
    return packet >> pos.x >> pos.y;
}