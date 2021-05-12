#include "client.h"
#include "game.h"
#include "server.h"
#include <iostream>
#include <stdio.h>
#include <sys/utsname.h>

int main() {
    Client client;
    int pause_flag = 0;
    // connect to local machine
    sf::IpAddress server_addr(sf::IpAddress::LocalHost);
    std::cout << "Address of server is: " << server_addr << std::endl;
    
    // connect to server
    client.connect(server_addr);
    unsigned short server_port = client.get_port();
    std::cout << "Port received from server: " << server_port << std::endl;

    sf::Clock clock;
    sf::Time elapsed;
    std::cout << "client number is " << client.number << std::endl;
    // window
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "aerohockey-game", sf::Style::Default);
    Game aerohockey = Game(window.getSize(), client.number + 1);
    std::cout << "aerohockey number is " << aerohockey.number << std::endl;
    sf::Image background_image;
    sf::Texture background_texture;
    sf::Sprite background;
    #ifdef __MACH__
        std::string path = "/Users/stassidelnikov/aerohockey-game";
    #else
        std::string path = std::experimental::filesystem::current_path().string();
    #endif
    background_image.loadFromFile(path + "/game/images/background.png");
    background_image.createMaskFromColor(sf::Color::White);
    background_texture.loadFromImage(background_image);
    background.setTexture(background_texture);
    background.setOrigin(background_image.getSize().x / 2, 0);
    background.setPosition(window.getSize().x / 2, aerohockey.scoreboard.getSize().y);



    // game loop
    
    sf::Vector2i mouse_pos;
    while (window.isOpen()) {

        bool received = true;
        bool updated = false;
        sf::Packet packet;

        // event polling

        sf::Event event;
        while (window.pollEvent(event)) {

            switch(event.type) {

                case sf::Event::Closed:
                    std::cout << "Closing window." << std::endl;
                    window.close();
                    break;

                case sf::Event::KeyPressed:
                    std::cout << "Key pressed." << std::endl;
                    if (event.key.code == sf::Keyboard::Escape) {
                        window.close();
                    }
                    if (event.key.code == sf::Keyboard::Space) {
                        pause_flag = (pause_flag == 0) ? 1 : 0;
                        //pause_flag = 1;
                    }
                    break;
            }
        }
        mouse_pos = sf::Mouse::getPosition(window);
        

        aerohockey.play(window);

        window.clear(sf::Color(0, 49, 83, 0));
        window.draw(background);
        aerohockey.draw_objects(window);
        window.display();

        elapsed = clock.getElapsedTime();

        if (elapsed > client.get_update_time(aerohockey)) {
            sf::Vector2f float_mouse_pos(mouse_pos);
            packet << float_mouse_pos;
            std::cout << "PAUSE " << pause_flag << std::endl;
            if (!pause_flag) {
                if (!client.send_updates(packet, server_addr, server_port)) {
                    std::cerr << "Error sending updates to server. " << std::endl;
                    std::cerr << std::endl;
                }

                std::cout << "Updates sent to server: " << mouse_pos.x << " " << mouse_pos.y << std::endl;
                packet.clear();
            }
            sf::IpAddress server_addr;
            unsigned short server_port;

            if (!client.receive_updates(packet, server_addr, server_port)) {
                std::cerr << "Error receiving updates from server. " << std::endl;
                std::cerr << std::endl;
                received = false;
            }

            sf::Vector2f pos;
            if (received) {
                packet >> float_mouse_pos >> pos;
            }
            //std::cout << "PUCK CORD " << pos.x << " " << pos.y << std::endl;
            aerohockey.puck.set_coord(pos);
            if (aerohockey.number == 1)
                aerohockey.striker2.set_coord(static_cast<sf::Vector2<float>>(mouse_pos));
            else
                aerohockey.striker1.set_coord(static_cast<sf::Vector2<float>>(mouse_pos));
            //std::cout << "Updated data: " << mouse_pos.x << " " << mouse_pos.y;
            pos = aerohockey.puck.get_coord();
            std:: cout << "puck: " << pos.x << " " << pos.y << std::endl;
            pos = aerohockey.striker1.get_coord();
            std:: cout << "striker1: " << pos.x << " " << pos.y << std::endl; 
            pos = aerohockey.striker2.get_coord();
            std:: cout << "striker2: " << pos.x << " " << pos.y << std::endl; 
            //std::cout << "Received from: " << server_addr << std::endl;
            //std::cout << "Port: " << server_port << std::endl;

            clock.restart();
        }

        // get updates and send to server
    }

    return 0;
}