#include "../include/game.h"

Game::Game(sf::Vector2u windowsize_) {
    sf::Vector2f windowsize = sf::Vector2f(windowsize_);
    scoreboard = Scoreboard("/home/sergey/aerohockey-game/game/images/scoreboard.png", {windowsize.x/2, 0});  
    striker1 = DynamicObject("/home/sergey/aerohockey-game/game/images/circle.jpg");
    striker2 = DynamicObject("/home/sergey/aerohockey-game/game/images/circle.jpg");
    puck = DynamicObject("/home/sergey/aerohockey-game/game/images/puck.jpeg");
   
}

void Game::play() {

    //get structure of coordinates and score from socket

    //striker1.update({50, 50}, {0, 0});
    //striker2.update({100, 50}, {0, 0});
    //puck.update({150, 50}, {0, 0});
    //scoreboard.update();

    //if (scoreboard.goalscored())
    //    start_position();
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