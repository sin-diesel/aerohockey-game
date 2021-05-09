#include "client.h"
#include "game.h"
#include <iostream>

int main() {
    Client client;
    
    // connect to local machine
    sf::IpAddress server_addr(sf::IpAddress::LocalHost);
    std::cout << "Address of server is: " << server_addr << std::endl;
    
    // connect to server
    client.connect(server_addr);

    //while (1) {
        sf::Packet packet;
        sf::Vector2f pos;
        pos.x = 1.0f;
        pos.y = 2.0f;
        packet << pos.x << pos.y;
        if (!client.send(packet, server_addr)) {
            std::cerr << "Failure in sending packet to server. " << std::endl;
        }
    //}

    return 0;
}