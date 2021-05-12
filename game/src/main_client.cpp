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
    sf::Vector2f left(-1.0f, -1.0f);
    sf::Vector2f right(1.0f, 1.0f);
    mouse_direction.x = 50.0f;
    mouse_direction.y = 50.0f;

    while (1) {
        bool received = true;
        bool updated = false;
        sf::Packet packet;
        //packet = client.process_input();
        elapsed = clock.getElapsedTime();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !updated) {
            packet << left.x << left.y;
            updated = true;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !updated) {
            packet << right.x << right.y;
            updated = true;
        }
        if (elapsed > client.get_update_time(game)) {

            //std::cout << "Time elapsed: " << elapsed.asMilliseconds() << std::endl;

            //packet << mouse_direction.x << mouse_direction.y;
            std::cout << "Sent data: " << mouse_direction.x << " "  << mouse_direction.y << std::endl;

            if (!client.send_updates(packet, server_addr, server_port)) {
                std::cerr << "Error sending updates to server. " << std::endl;
                std::cerr << std::endl;
            }

            std::cout << "Updates sent to server." << std::endl;
            packet.clear();
            updated = false;

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

    }

    return 0;
}