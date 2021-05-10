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
    unsigned short server_port = client.get_port();
    std::cout << "Port received from server: " << server_port << std::endl;

    
    
    sf::Clock clock;
    sf::Time elapsed;

    sf::Vector2f mouse_direction; 
    mouse_direction.x = 50.0f;
    mouse_direction.y = 50.0f;

    while (1) {
        bool received = true;
        //packet = client.process_input();
        elapsed = clock.getElapsedTime();
        if (elapsed > client.get_update_time(game)) {

            //std::cout << "Time elapsed: " << elapsed.asMilliseconds() << std::endl;

            sf::Packet packet;
            packet.clear();
            packet << mouse_direction.x << mouse_direction.y;
            std::cout << "Sent data: " << mouse_direction.x << " "  << mouse_direction.y << std::endl;

            if (!client.send_updates(packet, server_addr, server_port)) {
                std::cerr << "Error sending updates to server. " << std::endl;
                std::cerr << std::endl;
            }

            std::cout << "Updates sent to server." << std::endl;

            sf::IpAddress server_addr;
            unsigned short server_port;
            if (!client.receive_updates(packet, server_addr, server_port)) {
                std::cerr << "Error receiving updates from server. " << std::endl;
                std::cerr << std::endl;
                received = false;
            }

            if (received) {
                packet >> mouse_direction.x >> mouse_direction.y;
            }

            std::cout << "Updated data: " << mouse_direction.x << " "  << mouse_direction.y << std::endl;

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