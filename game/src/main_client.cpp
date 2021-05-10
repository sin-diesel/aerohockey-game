#include "client.h"
#include "game.h"
#include <iostream>

int main() {
    Client client;

    Game game;
    
    // connect to local machine
    sf::IpAddress server_addr(sf::IpAddress::LocalHost);
    std::cout << "Address of server is: " << server_addr << std::endl;
    
    // connect to server
    client.connect(server_addr);
    sf::Vector2f pos;
    pos.x = 0.0f;
    pos.y = 0.0f;
    

    sf::Clock clock;
    sf::Time elapsed;

    while (1) {
        //packet = client.process_input();
        elapsed = clock.getElapsedTime();
        if (elapsed > client.get_update_time(game)) {
            
            sf::Packet packet;
            pos.x += 1.0f;
            pos.y += 2.0f;
            packet << pos.x << pos.y;
            std::cout << "Time elapsed: " << elapsed.asMilliseconds() << std::endl;

            if (!client.send_updates(packet, server_addr)) {
                std::cerr << "Error sending updates to server. " << std::endl;
                std::cerr << std::endl;
            }

            std::cout << "Updates sent to server." << std::endl;

            sf::IpAddress server_addr;
            unsigned short server_port;
            if (!client.receive_updates(packet, server_addr, server_port)) {
                std::cerr << "Error receiving updates from server. " << std::endl;
                std::cerr << std::endl;
            }

            std::cout << "Received from: " << server_addr << std::endl;
            std::cout << "Port: " << server_port << std::endl;

            clock.restart();
        }


        // sf::Packet packet;
        // pos.x += 1.0f;
        // pos.y += 2.0f;
        // packet << pos.x << pos.y;
        // std::cerr << "Pos sent to server: " << pos.x << " " << pos.y << std::endl;
        // if (!client.send(packet, server_addr)) {
        //     std::cerr << "Failure in sending packet to server. " << std::endl;
        // }
    }

    return 0;
}