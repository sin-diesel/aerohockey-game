#include "../include/game.h"

//const char path[] = "/Users/stassidelnikov/aerohockey-game";

Game::Game(sf::Vector2u windowsize_, sf::IpAddress& addr, std::string path_):
    client(addr),
    path(path_),
    number(1) {

    struct utsname details;
    int ret = uname(&details);
    if (ret == 0){
        printf("Sysname: %s\n", details.sysname);
    }

    sf::Vector2f windowsize = sf::Vector2f(windowsize_);
    sf::Vector2f pos(600, 600);
    scoreboard = Scoreboard(path + "/game/images/scoreboard.png", {windowsize.x/2, 0}, path);  
    striker1 = ClientDynamicObject(path + "/game/images/striker.png", pos);
    pos.x -= 100;
    striker2 = ClientDynamicObject(path + "/game/images/striker.png", pos);
    pos.x += 200;
    puck = ClientDynamicObject(path + "/game/images/puck.png", pos);

    number = client.get_number() + 1;

    field_image.loadFromFile(path + "/game/images/background.png");
    field_image.createMaskFromColor(sf::Color::White);
    field_texture.loadFromImage(field_image);
    field.setTexture(field_texture);
    field.setOrigin(field_image.getSize().x / 2, 0);
    field.setPosition(windowsize.x / 2, scoreboard.getSize().y);
}

void Game::play(sf::RenderWindow& window) 
{
    sf::Packet packet;
    packet.clear();
    bool received = true;
    sf::Vector2f mouse_pos = sf::Vector2f(sf::Mouse::getPosition(window));

    packet << mouse_pos;
    if (!client.send_updates(packet)) {
        std::cerr << "Error sending updates to server. " << std::endl;
        std::cerr << std::endl;
    }
    //std::cout << "Updates sent to server: " << mouse_pos.x << " " << mouse_pos.y << std::endl;
    packet.clear();

    sf::IpAddress server_addr;
    unsigned short server_port;
    if (!client.receive_updates(packet, server_addr, server_port)) {
        std::cerr << "Error receiving updates from server. " << std::endl;
        std::cerr << std::endl;
        received = false;
    }

    sf::Vector2f pos, pos_st1, pos_st2;
    sf::Vector2i score;
    if (received) {
        packet >> pos_st1 >> pos_st2 >> pos >> score;
        std::cout << "YESS" << std::endl;
    
    packet.clear();
    std::cout << pos_st1.x << " " << pos_st1.y << std::endl << pos_st2.x << " " << pos_st2.y << std::endl << pos.x << " " << pos.y << std:: endl << score.x << " " << score.y << std::endl;
    scoreboard.update(score);
    //std::cout << "PUCK CORD " << pos.x << " " << pos.y << std::endl;
    puck.set_coord(pos);
    /*if (aerohockey.number == 1) {
        aerohockey.striker2.set_coord(float_mouse_pos);
    else
        aerohockey.striker1.set_coord(float_mouse_pos);*/
    striker1.set_coord(pos_st1);
    striker2.set_coord(pos_st2);
    //std::cout << "Updated data: " << mouse_pos.x << " " << mouse_pos.y;
    pos = puck.get_coord();
    //std:: cout << "puck: " << pos.x << " " << pos.y << std::endl;
    pos = striker1.get_coord();
    //std:: cout << "striker1: " << pos.x << " " << pos.y << std::endl; 
    pos = striker2.get_coord();}
    //std:: cout << "striker2: " << pos.x << " " << pos.y << std::endl; 
    //std::cout << "Received from: " << server_addr << std::endl;
    //std::cout << "Port: " << server_port << std::endl;
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

sf::Time Game::get_update_time()
{
    return network_update_time;
}
