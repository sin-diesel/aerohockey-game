#include "../include/game.h"

//const char path[] = "/Users/stassidelnikov/aerohockey-game";

Game::Game(sf::Vector2u windowsize_) {

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
    number = 1;
    sf::Vector2f windowsize = sf::Vector2f(windowsize_);
    sf::Vector2f pos(600, 600);
    scoreboard = Scoreboard(path + "/game/images/scoreboard.png", {windowsize.x/2, 0}, path);  
    striker1 = ClientDynamicObject(path + "/game/images/striker.png", pos);
    pos.x -= 100;
    striker2 = ClientDynamicObject(path + "/game/images/striker.png", pos);
    pos.x += 200;
    puck = ClientDynamicObject(path + "/game/images/puck.png", pos);
   
    puck.set_coord({windowsize.x / 2, windowsize.y / 2});  //temporary, just to look vizualization
    striker2.set_coord({windowsize.x * 3 / 4, windowsize.y / 2});  //temporary, just to look vizualization
    number = client.get_number() + 1;
}

void Game::play(sf::RenderWindow& window) 
{
    sf::Packet packet;
    bool received;
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
    if (received) {
        packet >> pos_st1 >> pos_st2 >> pos;
    }
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
    pos = striker2.get_coord();
    //std:: cout << "striker2: " << pos.x << " " << pos.y << std::endl; 
    //std::cout << "Received from: " << server_addr << std::endl;
    //std::cout << "Port: " << server_port << std::endl;
}

void Game::draw_objects(sf::RenderWindow& window) {
    striker1.draw(window);
    striker2.draw(window);
    puck.draw(window);
    scoreboard.draw(window);
}

Game::~Game() {}

void Game::update() {}

sf::Time Game::get_update_time()
{
    return network_update_time;
}
