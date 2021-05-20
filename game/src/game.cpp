#include "../include/game.h"

//const char path[] = "/Users/stassidelnikov/aerohockey-game";

Game::Game(sf::Vector2u windowsize_, sf::IpAddress& addr, std::string path_, int choice):
    client(addr, keyboard_control),
    path(path_),
    keyboard_control((choice == 2) ? true : false),
    number(client.get_number() + 1) {

    struct utsname details;
    int ret = uname(&details);
    if (ret == 0){
        printf("Sysname: %s\n", details.sysname);
    }
    if (keyboard_control)
        std::cout << "GAMEKEYBOARDCONTROL IS TRUE" << std::endl;
    sf::Vector2f windowsize = sf::Vector2f(windowsize_);
    sf::Vector2f pos(CENTER_X, CENTER_Y);
    scoreboard = Scoreboard(path + "/game/images/scoreboard.png", {windowsize.x/2, 0}, path);  
    striker1 = ClientDynamicObject(path + "/game/images/striker.png", pos);
    pos.x -= 200;
    striker2 = ClientDynamicObject(path + "/game/images/striker.png", pos);
    pos.x += 400;
    puck = ClientDynamicObject(path + "/game/images/puck.png", pos);

    //number = client.get_number() + 1;

    field_image.loadFromFile(path + "/game/images/background.png");
    field_image.createMaskFromColor(sf::Color::White);
    field_texture.loadFromImage(field_image);
    field.setTexture(field_texture);
    field.setOrigin(field_image.getSize().x / 2, 0);
    field.setPosition(windowsize.x / 2, scoreboard.getSize().y);
}

void Game::sending_mouse_pos(sf::Window& window)
{
    sf::Packet packet;
    packet << sf::Vector2f(sf::Mouse::getPosition(window));
    if (!client.send_updates(packet)) {
        std::cerr << "Error sending updates to server. " << std::endl;
        std::cerr << std::endl;
    }
    packet.clear();
}

void Game::send_key(int key)
{
    sf::Packet packet;
    packet << key;
    std::cout << key << " sended" << std::endl;
    if (!client.send_updates(packet)) {
        std::cerr << "Error sending updates to server. " << std::endl;
        std::cerr << std::endl;
    }
    packet.clear();
}

void Game::play(sf::RenderWindow& window) 
{
    if (!keyboard_control)
        sending_mouse_pos(window);
    bool received = true;
    sf::IpAddress server_addr;
    unsigned short server_port;
    sf::Packet packet;
    if (!client.receive_updates(packet, server_addr, server_port)) {
        std::cerr << "Error receiving updates from server. " << std::endl;
        std::cerr << std::endl;
        received = false;
    }
    if (received) {
        sf::Vector2f pos, pos_st1, pos_st2;
        sf::Vector2i score;
        packet >> pos_st1 >> pos_st2 >> pos >> score;
        packet.clear();
        std::cout << "ST1: " << pos_st1.x << " " << pos_st1.y << std::endl << "ST2: " << pos_st2.x << " " << pos_st2.y << std::endl << "PUCK: " << pos.x << " " << pos.y << std:: endl << score.x << " " << score.y << std::endl;
        scoreboard.update(score);
        puck.set_coord(pos);
        striker1.set_coord(pos_st1);
        striker2.set_coord(pos_st2);
    }
}

void Game::draw_objects(sf::RenderWindow& window) {
    window.draw(field);
    striker1.draw(window);
    striker2.draw(window);
    puck.draw(window);
    scoreboard.draw(window);
}

int Game::get_number() {
    return number;
}

void Game::set_number(int num) {
    number = num;
}

bool Game::get_type_control() {
    return keyboard_control;
}

sf::Time Game::get_update_time() {
    return network_update_time;
}
