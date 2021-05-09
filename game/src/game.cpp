#include "../include/game.h"

Game::Game() {
    striker1 = Striker();
    striker2 = Striker();
    puck = Puck();
    scoreboard = Scoreboard("/home/aerohockey-game/game/images/scoreboard.png");
}
void Game::start_position() {
    scoreboard.unscored();
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
    //striker2.draw(window);
    //puck.draw(window);
    //scoreboard.draw(window);
}

Game::~Game() {
    
}

void Game::render() {

}

void Game::update() {

}