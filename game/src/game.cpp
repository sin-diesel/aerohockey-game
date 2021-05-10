#include "../include/game.h"

Game::Game(sf::Vector2u windowsize_) {
    sf::Vector2f windowsize = sf::Vector2f(windowsize_);
    scoreboard = Scoreboard("/home/sergey/aerohockey-game/game/images/scoreboard.png", {windowsize.x/2, 0});  
    striker1 = DynamicObject("/home/sergey/aerohockey-game/game/images/striker.png");
    striker2 = DynamicObject("/home/sergey/aerohockey-game/game/images/striker.png");
    puck = DynamicObject("/home/sergey/aerohockey-game/game/images/puck.png");
   
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
    striker1.set_coord(mouse_pos); //temporary, just to look vizualization
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