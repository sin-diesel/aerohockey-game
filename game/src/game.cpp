#include "../include/game.h"
#include "../include/puck.h"

Game::Game() {

}

void Game::start_position() {
    scoreboard.unscored();
}

void Game::play() {

    //get structure of coordinates and score from socket
    
    leftputter.update(50, 100);
    rightputter.update(100, 100);
    puck.update(150, 100);
    scoreboard.update();

    if (scoreboard.goalscored())
        start_position();

    //leftputter.vizualise();
    //rightputter.vizualise()
}

Game::~Game() {
    
}

void Game::render() {

}

void Game::update() {

}