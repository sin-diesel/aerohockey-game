#include "../include/game.h"
#include "../include/puck.h"

Game::Game() {
    leftputter();
    rightputter();
    puck();
    scoreboard();
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

    leftputter.vizualize();
    //rightputter.vizualize()
    //puck.vizualize();
    //scoreboard.vizualize();
}

void Game::draw_objects(sf::RenderWindow window) {
    window.draw(puck.get_sprite())
    window.draw(leftputter.get_sprite());
    window.draw(rightputter.get_sprite());
    window.draw(scoreboard.get_sprite());
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