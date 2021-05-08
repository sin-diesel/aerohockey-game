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

    return 0;
}